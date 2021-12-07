extern "C"{
  #include <libavformat/avformat.h>
  //#include <libavcodec/avcodec.h>
  #include <stdio.h>
}

#include <iostream>
using namespace std;

class Media{
  private: 
  AVFormatContext *container= NULL;

  AVCodec *codec = NULL;
  AVCodecParameters *codecParameters =  NULL;
  AVCodecContext *codecContext; 

  int video_stream_index = -1;
  const char *filename;

  AVFrame *frame;
  AVPacket *packet;

  public:
  Media(int argc, const char *argv[]){
    if (argc < 2) {
      cout << "usage: " << argv[0] << " input_file" << endl;
    }
	else
	  filename= argv[1];
    this->containerFormatData();
	this->accessStreamCodec();
	this->frames();
    codecContext= avcodec_alloc_context3(codec);
	avcodec_parameters_to_context(codecContext, codecParameters);
	avcodec_open2(codecContext, codec, NULL);
  }

  void containerFormatData(){
    container= avformat_alloc_context();
    avformat_open_input(&container, filename, NULL, NULL);
  }

  void accessStreamCodec(){
    avformat_find_stream_info(container,  NULL);
    for (int i = 0; i < container->nb_streams; i++){
      AVCodecParameters *localCodecParameters =  NULL;
      localCodecParameters = container->streams[i]->
	    codecpar;

	  AVCodec *localCodec = NULL;
      localCodec= avcodec_find_decoder(localCodecParameters->codec_id);

      if(localCodecParameters->codec_type == 
	    AVMEDIA_TYPE_VIDEO){
        if(video_stream_index == -1){
		  video_stream_index= i;
		  codec= localCodec;
		  codecParameters= localCodecParameters;
		}
		printf("Video Codec: resolution %d x %d\n", 
          localCodecParameters->width, 
          localCodecParameters->height);
      } else if (localCodecParameters->codec_type== 
        AVMEDIA_TYPE_AUDIO){
        printf("Audio Codec: %d channels, sample rate %d\n", 
     	  localCodecParameters->channels, 
    	  localCodecParameters->sample_rate);
      }
    }
	codecContext= avcodec_alloc_context3(codec);    
    avcodec_parameters_to_context(codecContext, codecParameters);
	avcodec_open2(codecContext, codec, NULL);
  }

  int decodePacketToFrames(AVPacket *packet, 
						   AVCodecContext *codecContext,
						   AVFrame *frame){
    int response= avcodec_send_packet(codecContext,
	 							      packet);
	while(response >=0){
	cout << response << endl;
    printf("Frame: %d\n", 
		    codecContext->frame_number);
	  char frame_filename[1024];
      save_gray_frame(frame->data[0], 
					  frame->linesize[0],
					  frame->width,
					  frame->height,
					  frame_filename);
	}
    return 1;
  }

  void frames(){
    frame= av_frame_alloc();
	packet= av_packet_alloc();
	int response= 0;
	int how_many_packets_to_process= 0;
    while(av_read_frame(container, packet) >= 0){
	  if(packet->stream_index== video_stream_index){
        response= decodePacketToFrames(packet, codecContext, frame);
		if(response < 0) break;
		if (--how_many_packets_to_process <= 0) break;
	  }
	  av_packet_unref(packet);
	}
	avformat_close_input(&container);
    av_packet_free(&packet);
	av_frame_free(&frame);
	avcodec_free_context(&codecContext);
  }

  void save_gray_frame(unsigned char *buf, 
								 int wrap,
								int xsize,
						        int ysize,
						   char *filename){

    FILE *f;
	int i;
//    f= fopen(filename, "w");
 //   fprintf(f, "P5\n%d %d \n %d \n", xsize, ysize, 255);
//    for(i= 0; i< ysize; i++){
//	  fwrite(buf + i * wrap, 1, xsize, f);

   // fclose(f);
  }
};

int main(int argc, const char *argv[]){
  Media m = Media(argc, argv);
  return 0;
}
