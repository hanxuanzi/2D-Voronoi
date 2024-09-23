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
//回调函数，窗口大小改变时被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//用于处理输入的函数
void processInput(GLFWwindow* window);
//设置窗口大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//处理输入
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//检查是否按下ESC
		glfwSetWindowShouldClose(window, true);
}
//实现
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);//视口设置
}
//定义顶点着色器源代码字符串
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"}\0";
//片段着色器
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
//绘制维诺边片段着色器
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.541, 0.596, 0.557,1.0f);\n"
"}\n\0";

//设置  点  为圆形
//float r = distance(gl_PointCoord, vec2(0.5, 0.5));
////根据距离设置片元
//if (r < 0.5)
//{
//	// 方形区域片元距离几何中心半径小于0.5，像素颜色设置红色
//	FragColor = vec4(PointColor, PointAlpha);
//}
//else
//{
//	// 方形区域距离几何中心半径不小于0.5的片元剪裁舍弃掉：
//	discard;//这个函数很重要 就是像素的某一部分不显示
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
		
		//初始化
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//创建GLFW窗口
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "wo voronio ", NULL, NULL);//窗口实例
		if (window == NULL)
		{
			std::cout << "Filed to creat GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);//后续OpenGL渲染在此窗口上进行
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//设置回调函数

		//初始化GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//将 GLFW 提供的加载函数 glfwGetProcAddress 转换为 GLADloadproc 类型的函数指针
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		//-----------------------------------------------------------------------------
		//创建顶点着色器对象并编译
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//源代码与着色器绑定
		glCompileShader(vertexShader);//将源代码编译为课执行的着色器对象
		//获取编译状态并检查
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		//创建片段着色器对象并编译
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		//创建片段着色器2
		unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
		glCompileShader(fragmentShader1);
		glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//链接程序
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);//链接到着色器程序对象中
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
         }
		/*glDeleteShader(vertexShader);*/
		glDeleteShader(fragmentShader);
		//链接程序1
		unsigned int shaderProgram1 = glCreateProgram();
		glAttachShader(shaderProgram1, vertexShader);
		glAttachShader(shaderProgram1, fragmentShader1);
		glLinkProgram(shaderProgram1);//链接到着色器程序对象中
		glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader1);

		//------------------------------------------------------------------------------------
		
		//输入点的数量
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
	
		
		// 顶点数组(x,y,z坐标）,去重
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
		//将要绘制的三角形的顶点元素放入basePoint中
		vector<Tri> drawdelaunayTri = Tri::delaunayTriangulation(Temp);
		vector<Point> basePoint;
		for (auto& delaunayTri : drawdelaunayTri) {
			basePoint.push_back(delaunayTri.pA);
			basePoint.push_back(delaunayTri.pB);
			basePoint.push_back(delaunayTri.pC);
		}
		//将要绘制的维诺边的顶点元素放入Vpoint容器
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
	// 创建一个足够大的浮点数数组，以存储点的坐标信息。
	// 	float* vertices = new float[Temp.size() * 3]; 
	//	for (int id = 0; id < num; id++)
	//	{
	//		
	//		vertices[id * 3] = Temp[id].x/800-1;
	//		vertices[id * 3 + 1] = Temp[id].y /600-1; //归一化处理
	//		vertices[id * 3 + 2] = 0;
	//		cout << vertices[id * 3] << " " << vertices[id * 3 + 1] << " " << vertices[id * 3 + 2] << endl;
	//	}
	//============
	
		//unsigned int indices[] = {  
		//	0, 1, 3, 
		//	1, 2, 3  
		//};
		// ==========================================================================
		//生成顶点数组与顶点缓冲对象
		unsigned int VBO[2], VAO[2]/*, EBO*/;
		glGenVertexArrays(2, VAO);
		glGenBuffers(2, VBO);
		//glGenBuffers(1, &EBO);
		
		//绑定VAO
		glBindVertexArray(VAO[0]);
		//绑定VBO与顶点数据
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(Point)*basePoint.size(), basePoint.data(), GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * Temp.size(), Temp.data(), GL_STATIC_DRAW);
		//绑定索引缓冲对象
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		//设置顶点属性指针和启用顶点属性
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
		//-----
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * Vpoint.size(), Vpoint.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);

		//解绑当前VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//解绑VAO
		glBindVertexArray(0);
		//--------------------------------------------------------------------------
		//渲染循环
		while (!glfwWindowShouldClose(window))
		{
			//检测输入
			processInput(window);
			//设置清空颜色与清空
			glClearColor(0.3176, 0.7686, 0.8275, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			//绘制
			glUseProgram(shaderProgram);//启用指定着色器程序
			glBindVertexArray(VAO[0]);//绑定为当前VAO
			glPointSize(5.0f);//点的大小
			
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(GL_TRIANGLES, 0, basePoint.size());

			//绘制维诺边
			glUseProgram(shaderProgram1);
			glBindVertexArray(VAO[1]);
			glLineWidth(5.0f);
			glDrawArrays(GL_LINES, 0, Vpoint.size());
			//交换前后缓冲区
            glfwSwapBuffers(window);
			//处理窗口时间，如键盘输入等
			glfwPollEvents();
		}

		glDeleteVertexArrays(2, VAO);
		glDeleteBuffers(2, VBO);
		glDeleteProgram(shaderProgram);
	    glfwTerminate();
	    return 0;
}




