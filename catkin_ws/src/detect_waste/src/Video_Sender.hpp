#ifndef VIDEO
#define VIDEO
#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

namespace asio = boost::asio;
using asio::ip::udp;

class VideoSender {
public:
    VideoSender(const std::string& server_ip, const std::string& server_port)
    : io_context_(), socket_(io_context_, udp::endpoint(udp::v4(), 0)), server_endpoint_(*resolver_.resolve(udp::v4(), server_ip, server_port).begin()) {
    }

    void send(const cv::Mat& image) {
        std::vector<uchar> buf;
        std::vector<int> compression_params = {cv::IMWRITE_JPEG_QUALITY, 50};
        cv::imencode(".jpg", image, buf, compression_params);
        std::string serialized(buf.begin(), buf.end());
        socket_.send_to(asio::buffer(serialized), server_endpoint_);
    }

private:
    asio::io_context io_context_;
    udp::socket socket_;
    udp::resolver resolver_{io_context_};
    udp::endpoint server_endpoint_;
};

#endif
