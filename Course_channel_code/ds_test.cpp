#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// GF(2^10) parameters
#define MM 10              /* RS code over GF(2^10) */
#define NN 1023            /* NN=2^MM -1   length of codeword */
#define KK 512             /* KK=NN-2*TT    */
#define TT ((NN-KK)/2)     /* number of errors that can be corrected */

// Primitive polynomial for GF(2^10): x^10 + x^3 + 1
#define PP 0x409           /* 10000001001 in binary */

// Global arrays for Galois Field
int alpha_to[NN + 1];      /* Galois field conversion table */
int index_of[NN + 1];      /* Galois field conversion table */
int gg[NN - KK + 1];       /* generator polynomial coefficients */

// Function prototypes
void generate_gf();
void gen_poly();
void rs_encoder(int *codeword, int n, int *message, int k);
void rs_decoder_Euclidean(int *ded_codeword, int *rec_codeword, int n, int k);
void simulate_bsc_channel(int *rec_codeword, int *codeword, int n, double error_prob);

// Function to generate Galois Field GF(2^m)
void generate_gf() {
    int i, mask;
    
    mask = 1;
    alpha_to[MM] = 0;
    for (i = 0; i < MM; i++) {
        alpha_to[i] = mask;
        index_of[alpha_to[i]] = i;
        if (PP & (1 << i)) {
            alpha_to[MM] ^= mask;
        }
        mask <<= 1;
    }
    
    index_of[alpha_to[MM]] = MM;
    mask >>= 1;
    
    for (i = MM + 1; i < NN; i++) {
        if (alpha_to[i - 1] >= mask) {
            alpha_to[i] = alpha_to[MM] ^ ((alpha_to[i - 1] ^ mask) << 1);
        } else {
            alpha_to[i] = alpha_to[i - 1] << 1;
        }
        index_of[alpha_to[i]] = i;
    }
    
    index_of[0] = -1;
    alpha_to[NN] = 0;
}

// Function to generate generator polynomial for RS code
void gen_poly() {
    int i, j;
    gg[0] = 1;
    
    for (i = 1; i <= NN - KK; i++) {
        gg[i] = 1;
        for (j = i - 1; j > 0; j--) {
            if (gg[j] != 0) {
                gg[j] = gg[j - 1] ^ alpha_to[(index_of[gg[j]] + i) % NN];
            } else {
                gg[j] = gg[j - 1];
            }
        }
        gg[0] = alpha_to[(index_of[gg[0]] + i) % NN];
    }
    
    // Convert gg[] to index form for easier polynomial operations
    for (i = 0; i <= NN - KK; i++) {
        gg[i] = index_of[gg[i]];
    }
}

// RS Encoder function
void rs_encoder(int *codeword, int n, int *message, int k) {
    int i, j;
    int feedback;
    int bb[NN - KK];
    
    // Check parameters
    if (n != NN || k != KK) {
        printf("Invalid code parameters!\n");
        return;
    }
    
    // Initialize parity bytes
    for (i = 0; i < NN - KK; i++) {
        bb[i] = 0;
    }
    
    // Systematic encoding using LFSR
    for (i = KK - 1; i >= 0; i--) {
        feedback = index_of[message[i] ^ bb[NN - KK - 1]];
        
        if (feedback != -1) {
            for (j = NN - KK - 1; j > 0; j--) {
                if (gg[j] != -1) {
                    bb[j] = bb[j - 1] ^ alpha_to[(gg[j] + feedback) % NN];
                } else {
                    bb[j] = bb[j - 1];
                }
            }
            bb[0] = alpha_to[(gg[0] + feedback) % NN];
        } else {
            for (j = NN - KK - 1; j > 0; j--) {
                bb[j] = bb[j - 1];
            }
            bb[0] = 0;
        }
    }
    
    // Form codeword: message + parity
    for (i = 0; i < KK; i++) {
        codeword[i] = message[i];
    }
    for (i = 0; i < NN - KK; i++) {
        codeword[i + KK] = bb[i];
    }
}

// RS Decoder using Euclidean algorithm
void rs_decoder_Euclidean(int *ded_codeword, int *rec_codeword, int n, int k) {
    int i, j, u, q;
    int elp[NN - KK + 2][NN - KK], d[NN - KK + 2], l[NN - KK + 2], u_lu[NN - KK + 2];
    int count, syn_error, deg_omega;
    int tmp, num1, num2, den, discr_r;
    int lambda[NN - KK + 1], omega[NN - KK + 1];
    int root[TT], loc[TT], reg[TT];
    int recd[NN];
    
    // Check parameters
    if (n != NN || k != KK) {
        printf("Invalid code parameters!\n");
        return;
    }
    
    // Copy received codeword
    for (i = 0; i < NN; i++) {
        recd[i] = rec_codeword[i];
    }
    
    // Compute syndrome polynomial S(z)
    int s[NN - KK + 1];
    syn_error = 0;
    for (i = 1; i <= NN - KK; i++) {
        s[i] = 0;
        for (j = 0; j < NN; j++) {
            if (recd[j] != 0) {
                s[i] ^= alpha_to[(index_of[recd[j]] + (NN - KK - i + 1) * j) % NN];
            }
        }
        
        if (s[i] != 0) {
            syn_error = 1;
        }
        
        s[i] = index_of[s[i]];
    }
    
    if (!syn_error) {
        // No errors, copy received codeword to decoded codeword
        for (i = 0; i < NN; i++) {
            ded_codeword[i] = recd[i];
        }
        return;
    }
    
    // Initialize Euclidean algorithm tables
    for (i = 0; i <= NN - KK; i++) {
        for (j = 0; j < NN - KK; j++) {
            elp[i][j] = 0;
        }
        d[i] = 0;
        l[i] = 0;
        u_lu[i] = 0;
    }
    
    // Initial conditions
    d[0] = 0;           // Index form
    d[1] = s[1];        // Index form
    elp[0][0] = 0;      // Index form
    elp[1][0] = 1;      // Polynomial form
    
    for (i = 1; i < NN - KK; i++) {
        elp[0][i] = -1; // Index form
        elp[1][i] = 0;  // Polynomial form
    }
    
    l[0] = 0;
    l[1] = 0;
    u_lu[0] = -1;
    u_lu[1] = 0;
    
    // Begin Euclidean algorithm
    u = 0;
    do {
        u++;
        
        if (d[u] == -1) {
            l[u + 1] = l[u];
            for (i = 0; i <= l[u]; i++) {
                elp[u + 1][i] = elp[u][i];
                elp[u][i] = index_of[elp[u][i]];
            }
            d[u + 1] = d[u];
        } else {
            // Find q such that d[u] + q*d[u-1] = 0
            q = (NN - index_of[d[u]] + index_of[d[u - 1]]) % NN;
            
            // Update l[u+1]
            if (l[u] > l[u - 1] + u_lu[u - 1] - u_lu[u]) {
                l[u + 1] = l[u];
            } else {
                l[u + 1] = l[u - 1] + u_lu[u - 1] - u_lu[u];
            }
            
            // Update elp[u+1][]
            for (i = 0; i < NN - KK; i++) {
                elp[u + 1][i] = 0;
            }
            
            for (i = 0; i <= l[u - 1]; i++) {
                if (elp[u - 1][i] != -1) {
                    elp[u + 1][i + u_lu[u - 1] - u_lu[u]] = 
                        alpha_to[(index_of[elp[u - 1][i]] + q) % NN];
                }
            }
            
            for (i = 0; i <= l[u]; i++) {
                if (elp[u][i] != -1) {
                    elp[u + 1][i] ^= alpha_to[index_of[elp[u][i]]];
                }
            }
            
            // Convert elp[u+1][] to index form
            for (i = 0; i <= l[u + 1]; i++) {
                if (elp[u + 1][i] != 0) {
                    elp[u + 1][i] = index_of[elp[u + 1][i]];
                } else {
                    elp[u + 1][i] = -1;
                }
            }
            
            // Update d[u+1]
            d[u + 1] = 0;
            for (i = 0; i <= l[u + 1]; i++) {
                if (s[u + 1 - i] != -1 && elp[u + 1][i] != -1) {
                    d[u + 1] ^= alpha_to[(s[u + 1 - i] + elp[u + 1][i]) % NN];
                }
            }
            d[u + 1] = index_of[d[u + 1]];
        }
        
        u_lu[u + 1] = u_lu[u] + 1;
        
    } while (u < NN - KK && l[u + 1] <= TT);
    
    u++;
    
    if (l[u] > TT) {
        // Too many errors to correct
        for (i = 0; i < NN; i++) {
            ded_codeword[i] = recd[i];
        }
        return;
    }
    
    // Form polynomial lambda(z) = elp[u][]
    for (i = 0; i <= l[u]; i++) {
        if (elp[u][i] != -1) {
            lambda[i] = elp[u][i];
        } else {
            lambda[i] = -1;
        }
    }
    
    // Find roots of lambda(z)
    count = 0;
    for (i = 1; i <= NN && count < l[u]; i++) {
        tmp = 0;
        for (j = 0; j <= l[u]; j++) {
            if (lambda[j] != -1) {
                tmp ^= alpha_to[(lambda[j] + j * (NN - i)) % NN];
            }
        }
        
        if (tmp == 0) {
            root[count] = i;
            loc[count] = NN - i;
            count++;
        }
    }
    
    if (count != l[u]) {
        // Cannot find all roots
        for (i = 0; i < NN; i++) {
            ded_codeword[i] = recd[i];
        }
        return;
    }
    
    // Form omega(z) = s(z)*lambda(z) mod z^(2*TT)
    for (i = 0; i <= NN - KK; i++) {
        omega[i] = -1;
    }
    
    for (i = 0; i <= NN - KK - l[u]; i++) {
        tmp = 0;
        for (j = 0; j <= i; j++) {
            if (s[i + 1 - j] != -1 && lambda[j] != -1) {
                tmp ^= alpha_to[(s[i + 1 - j] + lambda[j]) % NN];
            }
        }
        omega[i] = index_of[tmp];
    }
    
    // Compute error values
    for (j = count - 1; j >= 0; j--) {
        num1 = 0;
        for (i = 0; i <= l[u]; i++) {
            if (lambda[i] != -1) {
                num1 ^= alpha_to[(lambda[i] + i * root[j]) % NN];
            }
        }
        
        num2 = 0;
        for (i = 0; i <= NN - KK - l[u]; i++) {
            if (omega[i] != -1) {
                num2 ^= alpha_to[(omega[i] + i * root[j]) % NN];
            }
        }
        
        den = alpha_to[(root[j] * (NN - 1 - 0) + NN) % NN];
        
        if (num1 != 0 && loc[j] >= 0) {
            recd[loc[j]] ^= alpha_to[(index_of[num2] - index_of[num1] + index_of[den] + NN) % NN];
        }
    }
    
    // Copy decoded codeword
    for (i = 0; i < NN; i++) {
        ded_codeword[i] = recd[i];
    }
}

// Simulate Binary Symmetric Channel
void simulate_bsc_channel(int *rec_codeword, int *codeword, int n, double error_prob) {
    for (int i = 0; i < n; i++) {
        // Convert to binary representation (each symbol is 10 bits)
        for (int j = 0; j < MM; j++) {
            double rand_val = (double)rand() / RAND_MAX;
            if (rand_val < error_prob) {
                // Flip this bit
                rec_codeword[i] ^= (1 << j);
            } else {
                // Keep the bit
                rec_codeword[i] |= (codeword[i] & (1 << j));
            }
        }
    }
}

// Test function
int main() {
    int message[KK];
    int codeword[NN];
    int rec_codeword[NN];
    int ded_codeword[NN];
    
    // Initialize GF tables and generator polynomial
    generate_gf();
    gen_poly();
    
    // Generate random message
    printf("Generating random message...\n");
    for (int i = 0; i < KK; i++) {
        message[i] = rand() & ((1 << MM) - 1); // Random 10-bit symbols
    }
    
    // Encode the message
    printf("Encoding message...\n");
    rs_encoder(codeword, NN, message, KK);
    
    // Simulate transmission over BSC
    printf("Simulating BSC channel with error probability 0.01...\n");
    simulate_bsc_channel(rec_codeword, codeword, NN, 0.01);
    //codeword[2] = 192;
    //codeword[8] = 123;
    
    // Decode the received codeword
    printf("Decoding received codeword...\n");
    rs_decoder_Euclidean(ded_codeword, rec_codeword, NN, KK);
    
    printf("%d\n",ded_codeword[2]);

    // Check for errors
    int errors = 0;
    for (int i = 0; i < KK; i++) {
        if (message[i] != ded_codeword[i]) {
            errors++;
        }
    }
    
    printf("Decoding completed with %d errors in message portion.\n", errors);
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    
    return 0;
}