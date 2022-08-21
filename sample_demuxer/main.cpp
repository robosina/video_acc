#include "NvCodec/NvDecoder/NvDecoder.h"
#include "Utils/NvCodecUtils.h"
#include "Utils/FFmpegDemuxer.h"
#include "Common/AppDecUtils.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <thread>

simplelogger::Logger *logger = simplelogger::LoggerFactory::CreateConsoleLogger();

void inThread(){

}
int main()
{
    ShowDecoderCapability();
    std::string szInFilePath = "/home/saeed/Desktop/SakhteIran3-03.480.mp4";

    ck(cuInit(0));
    int nGpu = 0;
    ck(cuDeviceGetCount(&nGpu));
    CUcontext cuContext = NULL;
    int iGpu = 0;

    createCudaContext(&cuContext, iGpu, 0);
    FFmpegDemuxer demuxer(szInFilePath.c_str());
    NvDecoder dec(cuContext, false, FFmpeg2NvCodecId(demuxer.GetVideoCodec()), NULL, false, false);
    int nVideoBytes = 0, nFrameReturned = 0, nFrame = 0;
    uint8_t *pVideo = NULL, **ppFrame;
    cv::Mat mat_bgr;
    std::vector<std::string> aszDecodeOutFormat = {"NV12", "P016", "YUV444", "YUV444P16"};
    cv::namedWindow("a", cv::WINDOW_NORMAL);
    do
    {
        demuxer.Demux(&pVideo, &nVideoBytes);
        dec.Decode(pVideo, nVideoBytes, &ppFrame, &nFrameReturned);
        if (!nFrame && nFrameReturned)
        {
            LOG(INFO) << dec.GetVideoInfo();
            LOG(INFO) << "Output format: " << aszDecodeOutFormat[dec.GetOutputFormat()];
        }

        if (nFrameReturned < 1)
            continue;
        nFrame += nFrameReturned;
        cv::Mat mat_yuv = cv::Mat(dec.GetHeight() * 1.5, dec.GetWidth(), CV_8UC1, ppFrame[nFrameReturned - 1]);
        cv::Mat mat_rgb = cv::Mat(dec.GetHeight(), dec.GetWidth(), CV_8UC3);
        cv::cvtColor(mat_yuv, mat_rgb, cv::COLOR_YUV2BGR_NV21);
        cv::cvtColor(mat_rgb, mat_bgr, cv::COLOR_RGB2BGR);

        cv::imshow("a", mat_bgr);
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    } while (nVideoBytes);

    ck(cuCtxDestroy(cuContext));
    LOG(INFO) << "End of process";

    return 0;
}
