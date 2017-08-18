#include "Stabilition.h"



int main() 
{
	
    VideoCapture vc;
    vc.open("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\MOV_track.avi");

	if(!vc.isOpened()) {
		return 0;
	}

    Mat frame,orig,orig_warped;

    Stabilition stabilition;

    while(true) {
        vc >> frame;
        if(frame.empty()) break;
        frame.copyTo(orig);

        stabilition.processImage(orig);

        Mat invTrans = stabilition.rigidTransform.inv(DECOMP_SVD);
        warpAffine(orig,orig_warped,invTrans.rowRange(0,2),Size());

        imshow("orig",orig_warped);

        waitKey(1);
    }
    vc.release();

}