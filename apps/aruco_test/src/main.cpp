/*
 * main.cpp
 *
 *  Created on: 15.07.2013
 *      Author: pavel
 */
#include <stdio.h>

#include <iostream>
#include <string>
#include <boost/program_options.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <aruco.h>

int main(int argc, char* argv[]) {

	namespace po = boost::program_options;

	std::string usage = "Usage: \n"
			"./apps/aruco_test/aruco_test -s web  -c <path-to-camera-parameter-file> -w <web-cam-number>\n"
			"./apps/aruco_test/aruco_test -s file -c <path-to-camera-parameter-file> -f <path-to-video-file>\n";

	po::options_description desc("Aruco Test general options");
	desc.add_options()("help,h", "Print help")
			("source,s",po::value<std::string>()->default_value("web"), "select source web camera or video file")
			("camfile,c", po::value<std::string>(), "select camera data file")
			("web,w", po::value<int32_t>()->default_value(0), "webcam number: 0, 1, ...")
			("wH,H", po::value<int32_t>()->default_value(480), "webcam image rows")
			("wW,W", po::value<int32_t>()->default_value(640), "webcam image columns")
			("file,f", po::value<std::string>(), "path to file")
			;
	po::variables_map vm;

	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
	} catch (const po::invalid_command_line_syntax& inv_syntax) {
		desc.print(std::cerr);
		return 1;
	}

	bool webcamSource = true;
	if (vm.count("help")) {
		desc.print(std::cerr);
		std::cout << usage << std::endl;
		return 0;
	}
	if (!vm.count("source")) {
		desc.print(std::cerr);
		return 1;
	}
	if (vm["source"].as<std::string>() == "web") {
		if (!vm.count("web")) {
			desc.print(std::cerr);
			return 1;
		}
	} else if (vm["source"].as<std::string>() == "file") {
		if (!vm.count("file")) {
			desc.print(std::cerr);
			return 1;
		}
		webcamSource = false;
	} else {
		std::cerr << "error: wrong source" << std::endl;
		desc.print(std::cerr);
		return 1;
	}
	if (!vm.count("camfile")) {
		std::cerr << "error: enter path to camera file" << std::endl;
		desc.print(std::cerr);
		return 1;
	}

	cv::VideoCapture vc;
	aruco::MarkerDetector md;
	aruco::CameraParameters cp;
	vector<aruco::Marker> markers;

	cp.readFromXMLFile(vm["camfile"].as<std::string>());

	if (webcamSource) {
		vc = cv::VideoCapture(vm["web"].as<int32_t>());
		vc.set(CV_CAP_PROP_FRAME_WIDTH, vm["wW"].as<int32_t>());
		vc.set(CV_CAP_PROP_FRAME_HEIGHT, vm["wH"].as<int32_t>());

	} else if (argc > 1) {
		vc = cv::VideoCapture(vm["file"].as<std::string>());
	}

	if (vc.isOpened()) {
		while (1) {
			cv::Mat im;
			if (vc.grab()) {
				if (vc.retrieve(im)) {

					static bool resize = false;
					if (!resize && im.rows && im.cols) {
						cp.resize(cv::Size(im.cols, im.rows));
						resize = true;
					}

					int64 tc = cv::getTickCount();
					md.detect(im, markers, cp.CameraMatrix, cv::Mat(), 1);
					double t = (double(cv::getTickCount() - tc)
							/ cv::getTickFrequency()) * 1000.0;

					char buf[100];
					snprintf(buf, 100, "M: %d, T: %f ms", int(markers.size()),
							double(t));
					cv::putText(im, buf, cv::Point(4, 12),
							cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0));

					cv::imshow("out", im);
				}
			}
			char c = cv::waitKey(1000 / 30);
			if (c == 27) {
				break;
			}
		}
	} else {
		printf("can't open VideoCapture");
		return 1;
	}
	return 0;
}

