#include "Tri.h"
#include<iostream>
#include "glad/glad.h"
#include "glfw3.h"
#include<set>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif


using namespace std;
//�ص����������ڴ�С�ı�ʱ������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//���ڴ�������ĺ���
void processInput(GLFWwindow* window);
//���ô��ڴ�С
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//��������
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//����Ƿ���ESC
		glfwSetWindowShouldClose(window, true);
}
//ʵ��
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);//�ӿ�����
}
//���嶥����ɫ��Դ�����ַ���
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"}\0";
//Ƭ����ɫ��
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	//float r = distance(gl_PointCoord, vec2(0.5, 0.5));\n"
"	//if (r < 0.5)\n"
"	//{\n"
"		FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"	//}\n"
"	//else\n"
"	//{\n"
"	//	discard;"
"	//}\n"
"}\n\0";
//����άŵ��Ƭ����ɫ��
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.541, 0.596, 0.557,1.0f);\n"
"}\n\0";

//����  ��  ΪԲ��
//float r = distance(gl_PointCoord, vec2(0.5, 0.5));
////���ݾ�������ƬԪ
//if (r < 0.5)
//{
//	// ��������ƬԪ���뼸�����İ뾶С��0.5��������ɫ���ú�ɫ
//	FragColor = vec4(PointColor, PointAlpha);
//}
//else
//{
//	// ����������뼸�����İ뾶��С��0.5��ƬԪ������������
//	discard;//�����������Ҫ �������ص�ĳһ���ֲ���ʾ
//}


int main()
{
	
	/*Point pu(0, 0);
	Point po(0, 2);
	Point pq(-1, 0);
	Point q(-1, 1);
	Point w(-1, -1);
	Line l1(po, pq);
	
	Line l2(pu, po);

	Line l3(q, w);
	vector<Line> common;
	common.push_back(l1);
	common.push_back(l2);
	bool id = Line::isinVector(common, l3);
	Point point = Line::findstartPoint(l1);
	point.out();
	cout << endl;*/
	
	

		//OpenGL------------------
		// -------------------------------------------------------------------------
		
		//��ʼ��
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//����GLFW����
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "wo voronio ", NULL, NULL);//����ʵ��
		if (window == NULL)
		{
			std::cout << "Filed to creat GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);//����OpenGL��Ⱦ�ڴ˴����Ͻ���
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//���ûص�����

		//��ʼ��GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//�� GLFW �ṩ�ļ��غ��� glfwGetProcAddress ת��Ϊ GLADloadproc ���͵ĺ���ָ��
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		//-----------------------------------------------------------------------------
		//����������ɫ�����󲢱���
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//Դ��������ɫ����
		glCompileShader(vertexShader);//��Դ�������Ϊ��ִ�е���ɫ������
		//��ȡ����״̬�����
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		//����Ƭ����ɫ�����󲢱���
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		//����Ƭ����ɫ��2
		unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
		glCompileShader(fragmentShader1);
		glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//���ӳ���
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);//���ӵ���ɫ�����������
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
         }
		/*glDeleteShader(vertexShader);*/
		glDeleteShader(fragmentShader);
		//���ӳ���1
		unsigned int shaderProgram1 = glCreateProgram();
		glAttachShader(shaderProgram1, vertexShader);
		glAttachShader(shaderProgram1, fragmentShader1);
		glLinkProgram(shaderProgram1);//���ӵ���ɫ�����������
		glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader1);

		//------------------------------------------------------------------------------------
		
		//����������
		int num;
		cin >> num;


		//test point
		/*Point p(0.0, 1.0);
		Point pd(0.0, 0.3);

		Point p2(-0.1, 0.0);
		Point p3(0.1, 0.0);
		Point p4(0.0, -0.9);
		Point p5(0.0, 0.0);
		Point p6(0.0, 0.5);
		Tri tri(p, p2, p3);
		
		cout << tri.isPointInTri(p5) << endl;*/
		//===================================
		///*Line commonedge(p2, p3);*/
		//vector<Tri> testtri;
		//testtri.push_back(tri1);
		//testtri.push_back(tri2);
		//
		//Tri tri;
		//for (auto& tri : testtri) {
		//	tri.pA.out();
		//	tri.pB.out();
		//	tri.pC.out();
		//	cout << endl;
		//}
		//tri.localOptimization(testtri);
		///*tri.swapD(tri1,tri2,commonedge,testtri);*/
		//cout << "================" << endl;
		//for ( auto& tri : testtri) {
		//	tri.pA.out();
		//	tri.pB.out();
		//	tri.pC.out();
		//	cout << endl;
		//}
		//=============================================
		
		/*vector<Point>testpoint;*/
		/*testpoint.push_back(p);
		testpoint.push_back(pd);*/
	
	/*	testpoint.push_back(p4);*/
		//testpoint.push_back(p2);
		//testpoint.push_back(p1);
		//testpoint.push_back(p4);
		//testpoint.push_back(p3);
		//testpoint.push_back(p1);
		//testpoint.push_back(p4);

	/*	testpoint.push_back(p1);
		testpoint.push_back(p2);
		testpoint.push_back(p3);
		testpoint.push_back(p);*/

        //vector<Tri> drawdelaunayTri = Tri::delaunayTriangulation(testpoint);
		//vector<Point> basePoint;
		//for (auto& delaunayTri : drawdelaunayTri) {
		//	basePoint.push_back(delaunayTri.pA);
		//	basePoint.push_back(delaunayTri.pB);
		//	basePoint.push_back(delaunayTri.pC);
		//}
		//cout << "" << basePoint.size() << endl;
	
		
		// ��������(x,y,z���꣩,ȥ��
		vector<Point> Temp = Point::SetPoint(num);
		set<Point> setData;
		for (auto& p : Temp)
		{
			setData.insert(p);
		}
		Temp.clear();
		for (auto& p : setData) {
			Temp.push_back(p);
		}
		setData.clear();
		//��Ҫ���Ƶ������εĶ���Ԫ�ط���basePoint��
		vector<Tri> drawdelaunayTri = Tri::delaunayTriangulation(Temp);
		vector<Point> basePoint;
		for (auto& delaunayTri : drawdelaunayTri) {
			basePoint.push_back(delaunayTri.pA);
			basePoint.push_back(delaunayTri.pB);
			basePoint.push_back(delaunayTri.pC);
		}
		//��Ҫ���Ƶ�άŵ�ߵĶ���Ԫ�ط���Vpoint����
		std::vector<Line> voronoiEdgesList;
		vector<Point> Vpoint;
		vector<Line> voronoiDram = Tri::VoronoiDiagramEdges(drawdelaunayTri,voronoiEdgesList);
		for (auto& voronoidram : voronoiDram) {
			Vpoint.push_back(voronoidram.pA);
			Vpoint.push_back(voronoidram.pB);
		}

		
	//========================================================================
		//float vertices[] = {
		//	0.5f,  0.5f, 0.0f, 
		//	0.5f, -0.5f, 0.0f, 
		//   -0.5f, -0.5f, 0.0f, 
		//};
	// ======
	// ����һ���㹻��ĸ��������飬�Դ洢���������Ϣ��
	// 	float* vertices = new float[Temp.size() * 3]; 
	//	for (int id = 0; id < num; id++)
	//	{
	//		
	//		vertices[id * 3] = Temp[id].x/800-1;
	//		vertices[id * 3 + 1] = Temp[id].y /600-1; //��һ������
	//		vertices[id * 3 + 2] = 0;
	//		cout << vertices[id * 3] << " " << vertices[id * 3 + 1] << " " << vertices[id * 3 + 2] << endl;
	//	}
	//============
	
		//unsigned int indices[] = {  
		//	0, 1, 3, 
		//	1, 2, 3  
		//};
		// ==========================================================================
		//���ɶ��������붥�㻺�����
		unsigned int VBO[2], VAO[2]/*, EBO*/;
		glGenVertexArrays(2, VAO);
		glGenBuffers(2, VBO);
		//glGenBuffers(1, &EBO);
		
		//��VAO
		glBindVertexArray(VAO[0]);
		//��VBO�붥������
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(Point)*basePoint.size(), basePoint.data(), GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * Temp.size(), Temp.data(), GL_STATIC_DRAW);
		//�������������
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		//���ö�������ָ������ö�������
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
		//-----
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * Vpoint.size(), Vpoint.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);

		//���ǰVBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//���VAO
		glBindVertexArray(0);
		//--------------------------------------------------------------------------
		//��Ⱦѭ��
		while (!glfwWindowShouldClose(window))
		{
			//�������
			processInput(window);
			//���������ɫ�����
			glClearColor(0.3176, 0.7686, 0.8275, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			//����
			glUseProgram(shaderProgram);//����ָ����ɫ������
			glBindVertexArray(VAO[0]);//��Ϊ��ǰVAO
			glPointSize(5.0f);//��Ĵ�С
			
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(GL_TRIANGLES, 0, basePoint.size());

			//����άŵ��
			glUseProgram(shaderProgram1);
			glBindVertexArray(VAO[1]);
			glLineWidth(5.0f);
			glDrawArrays(GL_LINES, 0, Vpoint.size());
			//����ǰ�󻺳���
            glfwSwapBuffers(window);
			//������ʱ�䣬����������
			glfwPollEvents();
		}

		glDeleteVertexArrays(2, VAO);
		glDeleteBuffers(2, VBO);
		glDeleteProgram(shaderProgram);
	    glfwTerminate();
	    return 0;
}




