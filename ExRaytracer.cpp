#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl/glut.h>
#include "gmath.h"

// 전역 변수
#define MAX_DEPTH 3
#define H 768
#define W 1024
unsigned char Image[H * W * 3];
std::vector<GSphere> SphereList;
std::vector<GLight> LightList;

// 콜백 함수 선언
void Render();
void Reshape(int w, int h);

// 광선 추적 함수
int GetIdx(int i, int j);
void CreateImage();
GVec3 RayTrace(GLine ray, int depth);
GVec3 RayTrace_in(GLine ray, int depth, int sidx);
GVec3 Phong(GPos3 P, GVec3 N, GSphere Obj);
bool intersect_line_sphere(GLine ray, int &sidx, double &t);
GPos3 intersectPos_sphere(GLine ray, int sidx, GPos3 &P);
GVec3 MultPos(GVec3 X, GVec3 Y);

int main(int argc, char **argv)
{
	// OpenGL 초기화, 윈도우 크기 설정, 디스플레이 모드 설정
	glutInit(&argc, argv);
	glutInitWindowSize(W, H);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// 윈도우 생성 및 콜백 함수 등록
	glutCreateWindow("RayTracer");
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	
	// 조명 설정
	GLight Light0;
	Light0.Pos.Set(500.0, 300.0, -100.0);
	Light0.Ia.Set(0.1, 0.1, 0.1);
	Light0.Id.Set(0.1, 0.1, 0.1);
	Light0.Is.Set(0.4, 0.4, 0.4);
	LightList.push_back(Light0);

	GLight Light1;
	Light1.Pos.Set(-300, 400, -100);
	Light1.Ia.Set(0.2, 0.2, 0.2);
	Light1.Id.Set(0.7, 0.7, 0.7);
	Light1.Is.Set(0.8, 0.8, 0.8);
	LightList.push_back(Light1);

	// 장면에 구를 배치한다.

	//색깔 구
	GSphere Sphere0;
	Sphere0.Pos.Set(0.0, 0.0, -450.0);
	Sphere0.Rad = 50.0;
	Sphere0.Ka.Set(0.8, 0.8, 0.0);
	Sphere0.Kd.Set(0.7, 0.7, 0.0);
	Sphere0.Ks.Set(0.9, 0.9, 0.9);
	Sphere0.ns = 8.0;
	SphereList.push_back(Sphere0);

	GSphere Sphere1;
	Sphere1.Pos.Set(-80, -50, -450.0);
	Sphere1.Rad = 45.0;
	Sphere1.Ka.Set(0.2, 0.2, 0.8);
	Sphere1.Kd.Set(0.0, 0.0, 0.7);
	Sphere1.Ks.Set(0.9, 0.9, 0.9);
	Sphere1.ns = 8.0;
	SphereList.push_back(Sphere1);

	GSphere Sphere2;
	Sphere2.Pos.Set(80, 50, -450.0);
	Sphere2.Rad = 45.0;
	Sphere2.Ka.Set(0.9, 0.0, 0.0);
	Sphere2.Kd.Set(0.7, 0.0, 0.0);
	Sphere2.Ks.Set(0.9, 0.9, 0.9);
	Sphere2.ns = 8.0;
	SphereList.push_back(Sphere2);

	GSphere Sphere3;
	Sphere3.Pos.Set(80, -50, -450.0);
	Sphere3.Rad = 40.0;
	Sphere3.Ka.Set(0.8, 0.2, 0.8);
	Sphere3.Kd.Set(0.7, 0.0, 0.7);
	Sphere3.Ks.Set(0.9, 0.9, 0.9);
	Sphere3.ns = 8.0;
	SphereList.push_back(Sphere3);

	GSphere Sphere4;
	Sphere4.Pos.Set(-30, 30, -300.0);
	Sphere4.Rad = 45.0;
	Sphere4.Ka.Set(0.0, 0.8, 0.8);
	Sphere4.Kd.Set(0.0, 0.7, 0.7);
	Sphere4.Ks.Set(0.9, 0.9, 0.9);
	Sphere4.ns = 8.0;
	SphereList.push_back(Sphere4);


	// 반투명 구

	GSphere Spherew1;
	Spherew1.Pos.Set(-30, -30, -400.0);
	Spherew1.Rad = 30.0;
	Spherew1.Ka.Set(1.0, 1.0, 1.0);
	Spherew1.Kd.Set(1.0, 1.0, 1.0);
	Spherew1.Ks.Set(1.0, 1.0, 1.0);
	Spherew1.ns = 8.0;
	SphereList.push_back(Spherew1);

	GSphere Spherew2;
	Spherew2.Pos.Set(30, -30, -400.0);
	Spherew2.Rad = 30.0;
	Spherew2.Ka.Set(1.0, 1.0, 1.0);
	Spherew2.Kd.Set(1.0, 1.0, 1.0);
	Spherew2.Ks.Set(1.0, 1.0, 1.0);
	Spherew2.ns = 8.0;
	SphereList.push_back(Spherew2);

	GSphere Spherew3;
	Spherew3.Pos.Set(30, 30, -400.0);
	Spherew3.Rad = 30.0;
	Spherew3.Ka.Set(1.0, 1.0, 1.0);
	Spherew3.Kd.Set(1.0, 1.0, 1.0);
	Spherew3.Ks.Set(1.0, 1.0, 1.0);
	Spherew3.ns = 8.0;
	SphereList.push_back(Spherew3);

	// 이미지를 생성
	CreateImage();

	// 이벤트를 처리를 위한 무한 루프로 진입한다.
	glutMainLoop();
	
	return 0;
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Render()
{
	// 칼라 버퍼와 깊이 버퍼 지우기
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 칼라 버퍼에 Image 데이터를 직접 그린다.
	glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, Image);
	
	// 칼라 버퍼 교환한다
	glutSwapBuffers();
}

void CreateImage()
{
	int x0 = -W / 2;
	int y0 = H / 2 - 1;
	double z = -(H / 2) / tan(M_PI * 15 / 180.0);
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			double x = x0 + j;
			double y = y0 - i;
			GLine ray(GPos3(0.0, 0.0, 0.0), GPos3(x, y, z));
			GVec3 Color = RayTrace(ray, 0);

			int idx = (H - 1 - i) * W * 3 + j * 3;
 			unsigned char r = (Color[0] > 1.0) ? 255 : Color[0] * 255;
 			unsigned char g = (Color[1] > 1.0) ? 255 : Color[1] * 255;
 			unsigned char b = (Color[2] > 1.0) ? 255 : Color[2] * 255;
			Image[idx] = r;
			Image[idx + 1] = g;
			Image[idx + 2] = b;
		}
	}
}


GVec3 RayTrace(GLine ray, int depth)
{	
	GVec3 C;
	if (depth++ > MAX_DEPTH)
		return C;

	double k_reflect = 0.3;
	double k_refract = 0.9;
	double n1 = 1.0f;
	double n2 = 0.9f;

	int sidx;	// 광선과 교차하는 가장 까가운 구의 인덱스
	double t;	// 교차점에서 광선의 파라미터 t
	if (intersect_line_sphere(ray, sidx, t))
	{
		// 구현...
		GPos3 P; //교차점
		GVec3 N, V, R;
		GLine ray_reflect, ray_refract;

		//반사광선 구하기
		P = ray.Eval(t);
		N = (P - SphereList[sidx].Pos).Normalize();
		V = -ray.v;
		R = (V - 2 * (N*V)*N).Normalize();
		ray_reflect = GLine(P, R);

		//굴절 광선구하기
		double cos2 = 1 - SQR(n1 / n2)*(1 - SQR(N*(-V)));
		if (cos2 < 0) //항상 양수
			cos2 = -cos2;

		GVec3 T = GVec3((n1 / n2)*(-V) - (SQRT(cos2) - (n1 / n2)*N*(V))*N).Normalize();
		ray_refract = GLine(P, T);



		//인덱스로 하지말고 Sphere클래스 안에 새로운 material이라는 변수를 두고 이름tag를 둔다.
		if(sidx==0)  // 반사광선만
			C = Phong(P, N, SphereList[sidx]) + k_reflect * RayTrace(ray_reflect, depth);
		
		else if(sidx==4) // 반사 + 굴절
			C = Phong(P, N, SphereList[sidx]) 
						+ k_reflect * RayTrace(ray_reflect, depth)
						+ k_refract * RayTrace_in(ray_refract, depth, sidx);
		
		else  // 굴절광선만
			C = Phong(P, N, SphereList[sidx]) + k_refract * RayTrace_in(ray_refract, depth, sidx);
	
	}
	return C;
}

GVec3 RayTrace_in(GLine ray, int depth, int sidx)
{
	GVec3 C;
	if (depth++ > MAX_DEPTH)
		return C;
	
	double k_refract = 0.9f;
	double n1 = 0.9f;
	double n2 = 1.0f;

	GPos3 P, newP; //교차점
	GVec3 N, V;
	GLine ray_refract;
	
	P = ray.p;
	V = ray.v;

	newP = intersectPos_sphere(ray, sidx, P);
	N = (newP - SphereList[sidx].Pos).Normalize();

	double cos2 = 1 - SQR(n1 / n2)*(1 - SQR(N*(-V)));
	if (cos2 < 0) //항상 양수
		cos2 = -cos2;

	GVec3 T = GVec3((n1 / n2)*(-V) - (SQRT(cos2) - (n1 / n2)*N*(V))*N).Normalize();
	ray_refract = GLine(newP, T);

	C = k_refract * RayTrace(ray_refract, depth);
	return C;
}


GVec3 Phong(GPos3 P, GVec3 N, GSphere Obj)
{
	GVec3 C;

	for(int i=0; i<LightList.size();i++){
		GVec3 L = (LightList[i].Pos - P).Normalize();
		GVec3 V = (GPos3(0.0, 0.0, 0.0) - P).Normalize();
		GVec3 R = (2 * (N *L) * N - L).Normalize();             // V 대신에 (-L)이 입사광선이 된다


		//C를 누적해야한다. (광원)
		C += MultPos(Obj.Ka, LightList[i].Ia) + MultPos(Obj.Kd, LightList[i].Id) * MAX(0.0, N * L) + MultPos(Obj.Ks, LightList[i].Is) * pow(MAX(0.0, V * R), Obj.ns) ;
	}	
	return C;
}

bool intersect_line_sphere(GLine ray, int &sidx, double &t)  // &는 출력값을 저장한다.
{
	double min_t = 10000.0;

	// for문을 돌면서 모든 Sphere를 돈다.
	for (int i = 0; i < SphereList.size(); i++) {
		GVec3 v, u;
		double a, b, t1, t2;

		v = ray.v.Normalize();
		u = ray.p - SphereList[i].Pos;

		a = -(u*v);
		b = SQR(u*v) - (SQR(norm(u)) - SQR(SphereList[i].Rad));

		t1 = a + SQRT(b);
		t2 = a - SQRT(b);

		double t0 = MIN(t1, t2);

		if (t0 < min_t) {
			sidx = i;
			min_t = t0;
		}
	}

		t = min_t;

		if (t == 10000.0)
			return false;
		else
			return true;
}

GPos3 intersectPos_sphere(GLine ray, int sidx, GPos3 &P) 
{
	GVec3 v, u;
	double a, b, t1, t2;

	v = ray.v.Normalize();
	u = ray.p - SphereList[sidx].Pos;

	a = -(u*v);
	b = SQR(u*v) - (SQR(norm(u)) - SQR(SphereList[sidx].Rad));


	//새로운 교차점은 무조건 +값이 나옴
	t1 = a + SQRT(b);
	//t2 = a - SQRT(b);

	//if (P == ray.Eval(t1))
	//	P = ray.Eval(t2);
	//else

		P = ray.Eval(t1);

	return P;
}

GVec3 MultPos(GVec3 X, GVec3 Y)
{
	GVec3 C;
	C[0] = X[0] * Y[0];
	C[1] = X[1] * Y[1];
	C[2] = X[2] * Y[2];
	return C;
}
