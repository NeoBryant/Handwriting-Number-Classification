#include <iostream>
#include "canny.h"
#include "SimpleImgProcess.h"
#include "HoughEdgeDetect.h"
#include "PaperModification.h"
#include "ImageSegmentation.h"
using namespace std;

int main() {
	time_t start, midterm, end;
	start = time(NULL);

	CImg<int> SrcImg, GrayImg, DownSampledImg, CannyImg, HoughSpaceImg, 
		Edge_Point_Img, SrcImgWithVertexAndEdge, PaperModifiedImg;
	/*
	SrcImg.load_bmp("Input/5.bmp");

	GrayImg = grayTheImg(SrcImg);
	//GrayImg.display("GrayImg");
	DownSampledImg = downSampleTheImg(GrayImg, DownSampledSquareSize);
	//DownSampledImg.display("DownSampledImg");
	CannyImg = canny(DownSampledImg, DownSampledImg._width, DownSampledImg._height);
	//CannyImg.display("EdgeImg");
	
	HoughEdgeDetect myHoughEdgeDetect(CannyImg);
	myHoughEdgeDetect.HoughTransAndDetectEdge();
	HoughSpaceImg = myHoughEdgeDetect.getHoughSpaceImage();
	//HoughSpaceImg.display("houghArray");
	
	Edge_Point_Img = myHoughEdgeDetect.getCannyGrayImageWithEdge();
	//Edge_Point_Img.display("Edge_Point_Img");

	SrcImgWithVertexAndEdge = myHoughEdgeDetect.getFinallyProcessedImage(SrcImg);
	SrcImgWithVertexAndEdge.display("Finally Processed Image");


	// 以下为A四纸矫正部分

	PaperModification myPaperModification(SrcImg);
	myPaperModification.setVertexSet(myHoughEdgeDetect.getTopFourVertexSet(), myHoughEdgeDetect.getDownSampledSize());

	PaperModifiedImg = myPaperModification.getModifiedPaper();

	end = time(NULL);
	cout << endl << endl << "==== PaperModification End: " << end - start << " seconds is used." << endl << endl;

	PaperModifiedImg.display("Paper Modified Image");
	//PaperModifiedImg.save("Output/Modification/5-Modification.bmp");
	*/

	//测试模式读取文件
	PaperModifiedImg.load_bmp("Output/Modification/5-Modification.bmp");
	// 以下为数字提取识别部分

	CImg<int> NewGraySrcImg, BinaryImg, HistogramImage, DividingImg, 
		ColoredNumberDividedImg, NumberDividedCircledImg;
	NewGraySrcImg = grayTheImg(PaperModifiedImg);
	//NewGraySrcImg.display("New Gray SrcImg");

	ImageSegmentation myImageSegmentation(NewGraySrcImg);
	myImageSegmentation.processBinaryImage(false);
	BinaryImg = myImageSegmentation.getBinaryImage();
	BinaryImg.display("Binary Img");
	//BinaryImg.save("Output/BinaryImage/withDilationY/5-BinaryImage.bmp");
	
	myImageSegmentation.numberSegmentationMainProcess();
	HistogramImage = myImageSegmentation.getHistogramImage();
	HistogramImage.display("Histogram Image");
	//HistogramImage.save("Output/HistogramImage/5-HistogramImage.bmp");
	DividingImg = myImageSegmentation.getImageWithDividingLine();
	DividingImg.display("Image With Dividing Line");
	ColoredNumberDividedImg = myImageSegmentation.getColoredNumberDividedImg();
	ColoredNumberDividedImg.display("Colored Number Divided Img");
	//ColoredNumberDividedImg.save("Output/ColoredNumberDividedImg/5-ColoredNumberDividedImg.bmp");
	NumberDividedCircledImg = myImageSegmentation.getNumberDividedCircledImg();
	NumberDividedCircledImg.display("Number Divided Circled Img");
	//NumberDividedCircledImg.save("Output/NumberDividedCircledImg/5-NumberDividedCircledImg.bmp");

	myImageSegmentation.saveSingleNumberImage("Output/SingleNumberImage/5/");
	return 0;
}