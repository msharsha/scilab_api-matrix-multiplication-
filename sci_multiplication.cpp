
extern "C" {
#include "api_scilab.h"
#include "Scierror.h"

int sci_multiply(char *fname, unsigned fname_len)
{
	SciErr sciErr;

	CheckInputArgument(pvApiCtx,2,2);							//setting number of input and output argumnets
	CheckOutputArgument(pvApiCtx,1,1);



	int *addvarone=NULL;
	int *addvartwo=NULL;
	sciErr=getVarAddressFromPosition(pvApiCtx,1,&addvarone);				// To get adrress of the input variable 1

	if (sciErr.iErr)
	{
		printError(&sciErr,0);
		return 0;

	}


	if ( !isDoubleType(pvApiCtx,addvarone) || isVarComplex(pvApiCtx,addvarone) )          // Checking the type of the variable

	{
		Scierror(999,"%s : Wrong type of input argument #%d:a real matrix expected\n",fname,1);
		return 0;

	}

	                                                                 //declaring variables for input and output matrices
	double *mat1=NULL;
	double *mat2=NULL;
	int m1=0,n1=0;
	int m2=0,n2=0;
	double *nmat=NULL;
	int i=0,j=0,k=0;                                                              // Reading matrix and checking for errors
	sciErr=getMatrixOfDouble(pvApiCtx,addvarone,&m1,&n1,&mat1);

	if (sciErr.iErr)
	{
		printError(&sciErr,0);
                return 0;
	}
  
       // getting address of second variable

	sciErr=getVarAddressFromPosition(pvApiCtx,2,&addvartwo);

	if (sciErr.iErr)
	{
		printError(&sciErr,0);
		return 0;

	}

	if ( !isDoubleType(pvApiCtx,addvartwo) || isVarComplex(pvApiCtx,addvartwo) )

	{
		Scierror(999,"%s : Wrong type of input argument #%d:a real matrix expected\n",fname,2);
		return 0;

	}

	sciErr=getMatrixOfDouble(pvApiCtx,addvartwo,&m2,&n2,&mat2);

	if (sciErr.iErr)
	{
		printError(&sciErr,0);
                return 0;
	}                                              
     //Application Code

     //if cols of mat1 are not equal to rows of mat2
	if(n1 != m2)
	{

		Scierror(999, "%s:invalid dimensions", fname,1);
		return 0;


	}
       //Normal Multiplication
	nmat = (double*)malloc(sizeof(double) * n2 * m1);
				                                
        for(i=0;i<n2;i++)

        {
                for (j=0;j<m1;j++)							

                {
                        for(k=0;k<m2;k++)

                        {
                                nmat[i*m1+j] += (*(mat2+i*m2+k))*(*(mat1+k*m1 +j));
                        }
			
                }
        }

       //assigning output

        sciErr= createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,m1,n2,nmat);

        free(nmat);

        if(sciErr.iErr)

	{
                printError(&sciErr,0);
                return 0;

        }
        AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
        return 0;

}

}





