#include "BinaryDataset.h"

void main()
{
	std::string filefolder = "F:\\graduation design\\butterflies material\\dataset_605512\\605512\\leedsbutterfly_dataset_v1.0\\leedsbutterfly\\test";
	BinaDataset binData;
	std::vector<std::string> fileLists = binData.getFileLists(filefolder); // load file name

	const int size_list = fileLists.size();
	std::cout << "image count: " << size_list << std::endl;
	/*
	for (int i = 0; i<fileLists.size(); i++)
	{
		char* curfile = new char[128];
		sprintf(curfile, "F:\\graduation design\\butterflies material\\butterflies\\my_test_img\\Samples\\%04d.jpg", i+85);
		string fileName = filefolder + "\\";
		fileName += fileLists[i];
		cv::Mat image = cv::imread(fileName);
		cv::imwrite(curfile, image);
		delete[] curfile;
	}
	*/
	
	std::vector<int> image_labels(size_list, 0);  // generate lables, here are all 0

	int count_class_k[10] = { 14, 29, 39, 54, 69, 86, 101,110,125,139 };
	int j = 0;
	for (int i = 0; i < 10; i++)
	{
		for (; j < count_class_k[i]; j++)
			image_labels[j] = i;
	}
	
	/*
	int m = 0;
	int n = 0;
	for (n = 0; n < 10; n++)
	{
		for (; m < count_class_k[n]; m++)
			cout << image_labels[m]<<endl;
	}
	*/
	std::string binfile = "F:\\graduation design\\butterflies material\\dataset_605512\\605512\\leedsbutterfly_dataset_v1.0\\leedsbutterfly\\test_bin\\test_batch.bin";
	binData.images2BinaryFile(filefolder, fileLists, image_labels, binfile);
}
