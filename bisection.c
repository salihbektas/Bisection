/*****************************************************************************/
/*bisection.c                                                                */
/*Salih Bektaş 131044006                                                     */
/*Gebze Tecnical University													 */
/*Numerical analysis homework 1												 */
/*****************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


double f(double x);
double bisection(double (*f)(double), double an, double bn, double pbefore,
				 double epsilon, int* order, int option);

int main(int argc, char const *argv[]) {
    double x = 0.0, an = 0.0, bn = 0.0, epsilon = 0.0, n = 0.0;
	int option = 0, i = 1, order = 1;

	/*console inputs check*/
	if(argc != 5)
	{
		printf("wrong usage.\n");
		printf("Usage:%s <start root> <end root> <stopping criterion>",argv[0]);
		printf(" <€ value>\n");
		exit(1);
	}


	if(strcmp(argv[3], "DISTANCE_TO_ROOT") == 0)
		option = 1;
	else if(strcmp(argv[3], "ABSOLUTE_ERROR") == 0)
		option = 2;
	else if(strcmp(argv[3], "RELATIVE_ERROR") == 0)
		option = 3;
	else
	{
		printf("Wrong stopping criterion\n");
		printf("Stopping criterion must be: \"DISTANCE_TO_ROOT\" or\n");
		printf("                            \"ABSOLUTE_ERROR\"   or\n");
		printf("                            \"RELATIVE_ERROR\"\n");
		exit(1);
	}

	/*Root entity control in range*/
	an = atof(argv[1]);
	bn = atof(argv[2]);
	if( f(an) * f(bn) > 0)
    {
        printf("No root in this range: %lf <= x <= %lf\n", an, bn);
		printf("Program terminated\n");
        exit(1);
    }

	epsilon = atof(argv[4]);

	/*Calculate theoretically required number of iterations*/
	n = fabs(an - bn);
	while(n/pow(2,i) > epsilon && i < 100)
	{
		++i;
	}

	/*If more than 100 iterations are needed to approach the root,
	 *the program is terminated.
	 */
	if(i > 100)
	{
		printf("Root wouldn't found 100 bisection steps.\n");
		printf("Program terminated.\n");
		exit(1);
	}


    x = bisection(&f, an, bn, 0, epsilon, &order, option);

    printf("Approximated root : %lf\n", x);
	printf("Number of iterations : %d\n", order);
	printf("Theoretically required number of iterations : %d\n", i);
    return 0;
}


/*Function to be applied to bisection, so f(x).
 *Rewrite this function as needed before compiling and running the program
 */
double f(double x)
{
    /*return pow(x,2) - 5*x - 6;*/
	/*return 2*x + 3*cos(x) - exp(x);*/
	/*return 3*x - exp(x);*/
	/*return pow(x,2) - 4*x + 4 - log(x);*/
	return x + 1 - 2*sin(M_PI*x);
}


/* Takes one function pointer,start and end values for root range,
 * approximated root from previous iteration, epsilon value,
 * numbers of iteration as a out-put paramater and take stopping criteria.
 *
 * Return approximated root.
 */
double bisection(double (*f)(double), double an, double bn, double pbefore,
				 double epsilon, int* order, int option)
{
    double pn = 0.0, result = 0.0, disToRoot = 0.0, absError = 0.0,
			relErrer = 0.0, stopping = 0.0;

	/*Calculation of the middle value of start and end values*/
    pn = (an + bn)/2;


    disToRoot = f(pn);
	absError = fabs(pn - pbefore);
	relErrer = fabs((pn - pbefore)/pn);

	/*Print each iteration step to the screen*/
	if(*order == 1)
		printf("Order | Absolute error | Relative error\n");
	else
		printf("%3d   |%15.5lf |%15.5lf\n",*order, absError, relErrer);

	/*Setting the stopping criterion*/
	if(option == 1)
		stopping = fabs(disToRoot);
	else if(option == 2)
		stopping = absError;
	else if(option == 3)
		stopping = relErrer;

	/*If the root is successfully approximated, set result*/
    if(stopping <= epsilon)
    {
        result = pn;
    }
	/* If the result of the middle value is the same as the result of the
	 * start value, set start value as a middle value, increment numbers of
	 * iteration and make recursive call
	 */
    else if(f(an) * f(pn) > 0)
    {
		*order += 1;
        result = bisection(f, pn, bn, pn, epsilon, order, option);
    }
	/* If the result of the middle value is the same as the result of the
	 * end value, set end value as a middle value, increment numbers of
	 * iteration and make recursive call
	 */
    else
    {
		*order += 1;
        result = bisection(f, an, pn, pn, epsilon, order, option);
    }

    return result;
}
/*****************************************************************************/
/*								end of bisection.c							 */
/*****************************************************************************/
