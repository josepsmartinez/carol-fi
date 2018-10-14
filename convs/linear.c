#include <time.h>
#include <stdio.h>

#define ImgSize 3
#define KernelSize 3
#define NumberOfKernels 3

float inputImage[ImgSize][ImgSize]=
{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

float outputImage[ImgSize][ImgSize];

float convKernel[KernelSize][KernelSize] =
{
    {0, 0, 0},
    {0, 2, 0},
    {0, 0, 0}
};

void simpleConvolution() {
  int imgX = 0, imgY = 0;

  int kernelX = 0, kernelY = 0;
  int kernelMiddle = (int) (KernelSize/2);

  int outputPixel = 0;
  
  for(imgX;imgX<ImgSize;imgX++){
    imgY = 0;
    for(imgY;imgY<ImgSize;imgY++){
      //printf("image_x %d , image_y %d \n", imgX, imgY);

      outputPixel = 0;
      int kernelImgX = imgX - kernelMiddle;
      int kernelImgY = imgY - kernelMiddle;
      //printf("kernel_image_x %d , kernel_image_y %d \n", kernelImgX, kernelImgY);


      for(kernelX=0;kernelX<KernelSize;kernelX++){
	for(kernelY=0;kernelY<KernelSize;kernelY++){

	  //printf("kernel_x %d , kernel_y %d \n", kernelX, kernelY);

	  // arrumar tratamento do kernel
	  if((kernelX+kernelImgX >= 0 ) && (kernelY+kernelImgX >= 0 ) && (kernelX+kernelImgX) < ImgSize && (kernelY+kernelImgY) < ImgSize){
	    //printf("%d x %d \t", inputImage[kernelImgX][kernelImgY], convKernel[kernelX][kernelY]);
	    outputPixel += inputImage[kernelImgX+kernelX][kernelImgY+kernelY] * convKernel[kernelX][kernelY];
	  }
	}
		  }
      outputImage[imgX][imgY] = outputPixel;
    }
  }
}
void printImg(float image[ImgSize][ImgSize]) {
  int imgX, imgY;
  for (imgX=0; imgX<ImgSize; imgX++)
  {
    for(imgY=0; imgY<ImgSize; imgY++)
      {
	printf("%f ", image[imgX][imgY]);
      }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int kernelNumber;
  
  printImg(inputImage);
  
  for (kernelNumber=0; kernelNumber<NumberOfKernels; kernelNumber++){
    simpleConvolution();
    printImg(outputImage);
  }

}
