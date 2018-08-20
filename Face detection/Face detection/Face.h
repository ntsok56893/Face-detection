#pragma once

/**
* Created by 05 on 2018/8/20.
*/

#include <iostream>
#include <string>

#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

namespace Face_detection {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_detection;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btn_detection = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_detection
			// 
			this->btn_detection->Location = System::Drawing::Point(99, 194);
			this->btn_detection->Name = L"btn_detection";
			this->btn_detection->Size = System::Drawing::Size(75, 23);
			this->btn_detection->TabIndex = 0;
			this->btn_detection->Text = L"Detection";
			this->btn_detection->UseVisualStyleBackColor = true;
			this->btn_detection->Click += gcnew System::EventHandler(this, &MyForm::btn_detection_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btn_detection);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btn_detection_Click(System::Object^  sender, System::EventArgs^  e) {

		Mat frame;
		Mat grayFrame;
		VideoCapture capture(0);
		string cascadeName = "haarcascade_frontalface_default.xml";
		CascadeClassifier face_cascade;

		if (!face_cascade.load(cascadeName)) {
			cout << "Error loading cascade file" << endl;
		}

		//選定視訊裝置，0為自動偵測
		while (true) {
			//擷取視訊
			capture.read(frame);
			//轉換灰階
			grayFrame = Mat(frame.size(), CV_8U);
			cvtColor(frame, grayFrame, CV_BGR2GRAY);

			vector<Rect> face;
			face_cascade.detectMultiScale(grayFrame, face, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(10, 10));
			
			for (size_t i = 0; i < face.size(); i++) {
				cv::Point pt1(face[i].x + face[i].width, face[i].y + face[i].height);
				cv::Point pt2(face[i].x, face[i].y);
				rectangle(frame, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0);
			}
			imshow("window", frame);
			int loh = 0;
			if (loh == 0) {
				imwrite("213.jpg", frame);
				loh++;
			}

			if (waitKey(33) >= 0)
			{
				break;
			}
		}
		capture.release();
	}
	};
}
