#ifndef LineFit_H_
#define LineFit_H_

typedef struct LineFitStruct * LineFit;

LineFit LineFit_Create(void);
void LineFit_Destroy(LineFit * self);

#endif
