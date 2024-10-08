#include <stdio.h>
int main(void){
    int w;
    double bmi,h;
    scanf("%d %lf",&w,&h);
    bmi = w/((h/100)*(h/100));
    if (bmi>=30){
        printf("BMI: %.4lf and you are obese",bmi);
    }else if (bmi>25){
        printf("BMI: %.4lf and you are overweight",bmi);
    }else if (bmi>18.6){
        printf("BMI: %.4lf and you are healthy",bmi);
    }else{
        printf("BMI: %.4lf and you are underweight",bmi);
}
                                return 0;
}