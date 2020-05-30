#pragma once



#define LINUX 1
// Set to 0 before compiling for Windows

#define CST_VAL 0
// 0 or 1

#define EOS_ID 0
// 0 for linearisation, 1 for quadratic fit

#define SMOOTHEN_EQ 1
// 0 for exponential, 1 for integrated exponential

#define INTEGRATE_PHI 1
// 0 for rectangles, 1 for trapezes


#define NB_POINTS 1
#define VARIABILITY 0.03

#define HIST_LEN_DIAG 200
#define HIST_LEN_STATE 200
#define ALPHA_NB_POINTS 200
// Any int > 0



// Do not modify :
#define NB_CST 9
#define NB_STT 4
