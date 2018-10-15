#include <time.h>
#include <stdio.h>

#include "malloc2d.h"

#define ImgSize 3
#define KernelSize 3
#define NumberOfKernels 3

void simpleConvolution(float** inputImage, float** outputImage, float** convKernel) {
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
void printImg(float** image) {
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
  float **inputImage = malloc_2d(ImgSize, ImgSize, 0.0);
  inputImage[0][0] = 1;
  inputImage[0][1] = 2;
  inputImage[0][2] = 3; //
  inputImage[1][0] = 4;
  inputImage[1][1] = 5;
  inputImage[1][2] = 6; //
  inputImage[2][0] = 7;
  inputImage[2][1] = 8;
  inputImage[2][2] = 9;

  float **outputImage = malloc_2d(ImgSize, ImgSize, 0.0);

  float **convKernel = malloc_2d(KernelSize, KernelSize, 0.0);
  convKernel[1][1] = 2;
  
  printImg(inputImage);
  
  for (int kernelNumber=0; kernelNumber<NumberOfKernels; kernelNumber++){
    simpleConvolution(inputImage, outputImage, convKernel);
    printImg(outputImage);
  }

}
