#ifndef MY_PID
#define MY_PID 1
#ifdef __cplusplus
extern "C"{
#endif
typedef struct{
    float SetPoint;		//
    float P;	        //proportion constants
    float I;		    //integrated constants
    float D;	        //derivative constants
    float LastError;	//last error
    float PrevError;	//last last error
    float SumError;		//error accumulation
    float currentV;        //current velocity   
}PIDer;

void initPID(PIDer* this, float P, float I, float D);

#ifdef __cplusplus
}
#endif

#endif