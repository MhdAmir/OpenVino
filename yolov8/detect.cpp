# include"yolov8.h"

struct TimeCounter {
  public:
    TimeCounter() : reset(true) {}
  
    float Count() {
      if (reset) {
        previous_time   = std::chrono::system_clock::now();
        reset = false;
      }

      current_time = std::chrono::system_clock::now();
      elapsed_time = current_time - previous_time;

      return elapsed_time.count();
    }

    void Reset() { 
      reset = true; 
    }

  private:
    std::chrono::time_point<std::chrono::system_clock> current_time, previous_time;
    std::chrono::duration<float> elapsed_time;

    bool reset;
};

int main(int argc, char* argv[]) {
    TimeCounter time_;
    // try{
        // if(argc!=3){
            // std::cout<<"Usage:"<<argv[0]<<" <path_to_model> <path_to_image>"<<std::endl;
            // return EXIT_FAILURE;
        // }
        const std::string input_model_path {argv[1]};
        // const std::string input_image_path {argv[2]}; 
        cv::VideoCapture cap(4);
        Config config = { 0.1,0.4,0.4,320,320, input_model_path}; 
        clock_t start, end;
        YOLOV8 yolomodel(config);
        cv::Mat frame;
        int counterFps = 0;
        while(true){
            if(time_.Count() >= 1){
                fprintf(stderr, "FPS >> %d\n\n", counterFps);
                counterFps = 0;
                time_.Reset();
            }
            cap >> frame;
            counterFps++;
            start = clock();
            // cv::cvtColor(frame, bgrFrame, cv::COLOR_BGR2RGB);
            yolomodel.detect(frame);
            end = clock();
            cv::imshow("frame", frame);
            
            if(cv::waitKey(1)==27)break;
            // std::cout << "infer time = " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;

        }
        // cv::Mat img = cv::imread(input_image_path);

        // cv::imwrite("hasil.jpg", img);
    // }catch (const std::exception& ex){
        // std::cerr << ex.what()<<std::endl;
        // return EXIT_FAILURE;
    // }
    // return EXIT_SUCCESS;

}

