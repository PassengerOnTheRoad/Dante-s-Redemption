#define _CRT_SECURE_NO_WARNINGS        //��ֹ�ļ���ȫ���� https://blog.csdn.net/netyeaxi/article/details/80439407 ���sprintf ��������Ŀ����CԤ�����������_CRT_SECURE_NO_DEPRECATE
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>
#include <time.h>
#include <stdlib.h>

#pragma comment(lib,"Winmm.lib")
#define width 1400                            //���ڴ�С
#define high 700

IMAGE map;                                                                      //��ͼ
IMAGE menu;
IMAGE dead;
IMAGE imgzj;
IMAGE imgzjzz;
IMAGE imggj;
IMAGE imggjz;
IMAGE imgty;
IMAGE imgtyz;
float zjx, zjy;                                                                 //��������
float jtx, jty;                                                                 //��ͼ��ͷ����
float jtw = 1300, jth = 700;
float e1x, e1y, e2x, e2y, e3x, e3y, e4x, e4y, ldx, ldy, lx, ly;                 //����NPC����
float dj1x, dj1y;                                                                 //��������
int hp, isdead, kill1, kill2, kill3, kill4;                 //����״̬
int gamestatus;       //0Ϊ��ʼ����,1Ϊ������Ϸ��2Ϊ������Ϸ��3Ϊ��ͣ��Ϸ

FILE *mem;

struct dongzuo{
	int righti , rightj , lefti , leftj , zji , zjj , ygji , ygjj , zgji , zgjj ;  //����ͼƬλ����ʾ����
	int gji , gjj ;                                                             //��������
	int ii ;                                                                   //���ƶ�����������
	int ztyi, ytyi,tyi,tyj;
}dz{0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0};
int main()                      //������
{
	void startup();           //��Ϸ��� ��ʼ�� �˵� ���� ����
	void startmenu();
	void pausemenu();
	void show(dongzuo &);
	void updatewithoutinput();
	void updatewithinput(dongzuo &);
	void save();       //�浵�����
	void read();
	void gameover();    //gameover
	startup();
	while (1) {
		show(dz);
		updatewithoutinput();
		updatewithinput(dz);
	}
	gameover();
	return 0;
}
void save() {         //https://blog.csdn.net/baidu_30000217/article/details/53220036 �浵�����̳�CSDN

					  //���Լ���һЩ״̬��Ϣ

					  //�򿪴浵�ļ�
	if ((mem = fopen("memory.txt", "w+")) == NULL) {
		fprintf(stderr, "Can't open memory.txt!\n");
		exit(1);
	}
	fclose(mem);
}
void read(void) {
	//��ȡ��Ϸ�浵
	if ((mem = fopen("memory.txt", "r")) == NULL) {
		fprintf(stderr, "No Game Cache Here!\n");
		exit(2);
	}

	fclose(mem);
}
void startmenu()
{
	putimage(0, 0, &menu);
	setbkmode(TRANSPARENT);  //�����ں�ģʽ͸��
	settextcolor(WHITE);
	settextstyle(50, 0, "����");
	outtextxy(width*0.4, high*0.2, "1 �µĿ�ʼ");
	outtextxy(width*0.4, high*0.3, "2 ��ȡ�浵");
	outtextxy(width*0.4, high*0.4, "3 �˳���Ϸ");
	settextcolor(YELLOW);
	settextstyle(20, 0, "����");
	outtextxy(width*0.3, high*0.6, "�밴1����ʼ��Ϸ��2��������3���˳���Ϸ");
	outtextxy(width*0.3, high*0.65, "WASDΪ�������JΪ��������KΪ��Ծ��");
	outtextxy(width*0.3, high*0.7, "ESC����ͣ��Ϸ");
	outtextxy(width*0.3, high*0.75, "����ɵ����ľ���");
	FlushBatchDraw();           //beginbatchdrawֱ���������Ż���
	Sleep(2);
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == '1') { gamestatus = 1; }
		else if (input == '2') { read(); gamestatus = 1; }
		else if (input == '3') { gamestatus = 2; exit(0); }
	}
}
void startup()
{
	mciSendString("open .\\resource\\CryforYou.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	initgraph(width, high);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "�����ľ���");
	loadimage(&map, ".\\resource\\bk1.jpg");
	loadimage(&menu, ".\\resource\\hei.jpg");
	loadimage(&imgzj, ".\\resource\\xz.jpg");
	loadimage(&imgzjzz, ".\\resource\\xzzz.jpg");
	loadimage(&imggj, ".\\resource\\gj.jpg");
	loadimage(&imggjz, ".\\resource\\gjz.jpg");
	loadimage(&imgtyz, ".\\resource\\tyz.jpg");
	loadimage(&imgty, ".\\resource\\ty.jpg");
	//loadimage(&dead, ".\\resource\\boom.jpg");
	zjx = 50;
	zjy = 430;
	jtx = 0;
	jty = 100;
	e1x = e1y = e2x = e2y = e3x = e3y = e4x = e4y = ldx = ldy = lx = ly = 0;//ldΪ����lΪ��
	dj1x = 0;
	dj1y = 0;
	hp = 100;
	isdead = 0;
	kill1 = 0;
	kill2 = 0;
	kill3 = 0;
	kill4 = 0;
	BeginBatchDraw();
	gamestatus = 0;
	if (gamestatus == 0)startmenu();
}

void pausemenu() {
	clearrectangle(0, 0, width - 1, high - 1);
	putimage(0, 0, &menu);
	setbkmode(TRANSPARENT);  //�����ں�ģʽ͸��
	settextcolor(WHITE);
	settextstyle(50, 0, "����");
	outtextxy(width*0.4, high*0.2, "1 ������Ϸ");
	outtextxy(width*0.4, high*0.3, "2 ������Ϸ");
	outtextxy(width*0.4, high*0.4, "3 �˳���Ϸ");
	settextcolor(YELLOW);
	settextstyle(20, 0, "����");
	outtextxy(width*0.3, high*0.6, "�밴1����ʼ��Ϸ��2��������3���˳���Ϸ");
	outtextxy(width*0.3, high*0.65, "WASDΪ�������JΪ��������KΪ��Ծ��");
	outtextxy(width*0.3, high*0.7, "ESC����ͣ��Ϸ");
	outtextxy(width*0.3, high*0.75, "����ɵ����ľ���");
	FlushBatchDraw();           //beginbatchdrawֱ���������Ż���
	Sleep(2);
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == '1') { gamestatus = 1; }
		else if (input == '2') { save(); gamestatus = 1; }
		else if (input == '3') { gamestatus = 2; exit(0); }
	}
}
void show(dongzuo &dzij) {
	if (gamestatus == 1 && isdead == 0 && dzij.ii == 0) 
	{
		//��Ϸ������ʾ 
		//clearrectangle(0, 0, width - 1, high - 1);
		putimage(0, 50, jtw + 100, jth, &map, 0, 50);
		putimage(zjx, zjy, 260, 270, &imgzjzz, dzij.zji * 260 + 2, dzij.zjj * 270, NOTSRCERASE);
		putimage(zjx, zjy, 260, 270, &imgzj, dzij.zji * 260 + 2, dzij.zjj * 270, SRCINVERT);
	}
	else if(gamestatus == 1 && isdead == 0 && dzij.ii ==1){
		putimage(0, 50, jtw + 100, jth, &map, 0, 50);
		putimage(zjx - 50, zjy-150 , 400, 400, &imggjz, dzij.gji * 400, dzij.gjj * 400, NOTSRCERASE);
		putimage(zjx - 50, zjy-150 , 400, 400, &imggj, dzij.gji * 400, dzij.gjj * 400, SRCINVERT);
	/*	if (dzij.ii == 6) { dzij.ii = 0;
		putimage(zjx, zjy, 260, 270, &imgzjzz, dzij.zji * 260 + 2, dzij.zjj * 270, NOTSRCERASE);
		putimage(zjx, zjy, 260, 270, &imgzj, dzij.zji * 260 + 2, dzij.zjj * 270, SRCINVERT);
		}*/
		}
	else if (gamestatus == 1 && isdead == 0 && dzij.ii == 2) {
		putimage(0, 50, jtw + 100, jth, &map, 0, 50);
		putimage(zjx , zjy , 260, 297, &imgtyz, dzij.tyi * 260, dzij.tyj * 297, NOTSRCERASE);
		putimage(zjx , zjy , 260, 297, &imgty, dzij.tyi * 260, dzij.tyj * 297, SRCINVERT);
	}
	else if (gamestatus == 0)
		startmenu();
	else if (gamestatus == 3)
		pausemenu();
	//״̬
	FlushBatchDraw();
	Sleep(2);
}
void updatewithoutinput() {
	if (isdead == 0) {
		//����״̬
	}

}
void updatewithinput(dongzuo &dzij) {
	if (isdead == 0&&gamestatus==1) {
		char input;
		if (_kbhit()) {
			input = _getch();
			if (input == 'd') {
				dzij.ytyi = 0, dzij.ztyi = 0;
				clearrectangle(zjx-50, zjy-170, zjx + 450, zjy + 570);
				dzij.lefti = 0, dzij.leftj = 2;  //ˢ��
				dzij.zgji = 0, dzij.zgjj = 2, dzij.ygji = 0, dzij.ygjj = 0;
				dzij.ii = 0;
				dzij.righti++;
				zjx += 27;
				/*putimage(zjx, zjy, 260, 270, &imgzjzz, righti * 260 + 2, 0, NOTSRCERASE);
				putimage(zjx, zjy, 260, 270, &imgzj, righti * 260 + 2, 0, SRCINVERT);*/
				FlushBatchDraw();
				if (dzij.righti == 6&&dzij.rightj==0) { dzij.righti = 0;  dzij.rightj = 1; }  //���i=6�� i=0��j=1 i=12��i=0��j=0��i=18��i=0��j=1��
			    else if (dzij.rightj==1&&dzij.righti==6) { dzij.righti = 0;  dzij.rightj = 0; }
				dzij.zji = dzij.righti, dzij.zjj = dzij.rightj;
			}
			else if (input == 'a') {
				dzij.ytyi = 0, dzij.ztyi = 0;
				clearrectangle(zjx - 50, zjy - 170, zjx + 450, zjy + 570);
				dzij.righti = 0, dzij.rightj = 0;  //ˢ��
				dzij.zgji = 0, dzij.zgjj = 2, dzij.ygji = 0, dzij.ygjj = 0;
				dzij.ii = 0;
				dzij.lefti++;
				zjx -= 27;
				FlushBatchDraw();
				if (dzij.lefti == 6&&dzij.leftj==2) { dzij.lefti = 0;  dzij.leftj = 3; }  //���i=6�� i=0��j=1 i=12��i=0��j=0��i=18��i=0��j=1��
			    else if (dzij.leftj==3&&dzij.lefti==6) { dzij.lefti = 0;  dzij.leftj = 2; }
				dzij.zji = dzij.lefti, dzij.zjj = dzij.leftj;
			}
			 else if (input == 'j')
				{                           //��J��ʧԭͼ
				 dzij.ii =1;
				 dzij.ytyi = 0,dzij.ztyi=0;
					if (dzij.zjj < 2)
					{
						clearrectangle(zjx-50, zjy-170, zjx + 450, zjy + 570);
						dzij.zgji = 0,dzij.zgjj=2;
						dzij.righti = 0, dzij.rightj = 0, dzij.lefti = 0, dzij.leftj = 2;  //ˢ��
						dzij.ygji++;
						zjx ++;
						FlushBatchDraw();
						Sleep(5);
						if (dzij.ygji == 3 && dzij.ygjj == 0) { dzij.ygji = 0;  dzij.ygjj = 1; }  
						else if (dzij.ygjj == 1 && dzij.ygji == 3) { dzij.ygji = 0;  dzij.ygjj = 0; }
						dzij.gji = dzij.ygji, dzij.gjj = dzij.ygjj;
					}
					else if (dzij.zjj >=2) {
						clearrectangle(zjx - 50, zjy - 170, zjx + 450, zjy + 570);
						dzij.ygji = 0, dzij.ygjj = 0;
						dzij.righti = 0, dzij.rightj = 0, dzij.lefti = 0, dzij.leftj = 2;  //ˢ��
						dzij.zgji++;
						zjx --;
						FlushBatchDraw();
						Sleep(5);
						if (dzij.zgji == 3 && dzij.zgjj == 2) { dzij.zgji = 0;  dzij.zgjj = 3; }
						else if (dzij.zgjj == 3 && dzij.zgji == 3) { dzij.zgji = 0;  dzij.zgjj = 2; }
						dzij.gji = dzij.zgji, dzij.gjj = dzij.zgjj;
					}	
			  }
			 else if (input == 'k') {
				 dzij.ii = 2;
				 while(dzij.zjj < 2) {
					 clearrectangle(zjx - 50, zjy - 170, zjx + 450, zjy + 570);
					 dzij.ztyi = 0;
					 dzij.righti = 0, dzij.rightj = 0, dzij.lefti = 0, dzij.leftj = 2;  //ˢ��
					 dzij.ytyi++;
					 if (dzij.ytyi < 4)
						 zjy -= 100;
					 else zjy +=100;
					 //FlushBatchDraw();
					 /*time_t begin = time(NULL);
					 time_t end, delay = 1;*/
					/* do {
						 end = time(NULL);  putimage(0, 50, jtw + 100, jth, &map, 0, 50);
						 putimage(zjx, zjy , 260, 297, &imgtyz, dzij.tyi * 260, dzij.tyj * 297, NOTSRCERASE);
						 putimage(zjx, zjy , 260, 297, &imgty, dzij.tyi * 260, dzij.tyj * 297, SRCINVERT); FlushBatchDraw();
					 } while (end - begin < delay);*/
					 SYSTEMTIME begin,end;
					 int be, en;
					 GetLocalTime(&begin);
					 do {
						 GetLocalTime(&end);
						 putimage(0, 50, jtw + 100, jth, &map, 0, 50);
						 putimage(zjx, zjy, 260, 297, &imgtyz, dzij.tyi * 260, dzij.tyj * 297, NOTSRCERASE);
						 putimage(zjx, zjy, 260, 297, &imgty, dzij.tyi * 260, dzij.tyj * 297, SRCINVERT); FlushBatchDraw();
					 } while (end.wMilliseconds - begin.wMilliseconds < 70);
					 if (dzij.ytyi == 6) { dzij.ytyi = 0; break; }
					 dzij.tyi = dzij.ytyi, dzij.tyj = 0;
				 }
				 while(dzij.zjj >= 2) {
					 clearrectangle(zjx - 50, zjy - 170, zjx + 450, zjy + 570);
					 dzij.ytyi = 0;
					 dzij.righti = 0, dzij.rightj = 0, dzij.lefti = 0, dzij.leftj = 2;  //ˢ��
					 dzij.ztyi++;
					 if(dzij.ztyi<=3)
					 zjy -= 100;
					 else zjy += 100;
					 FlushBatchDraw();
					 Sleep(500);
					 if (dzij.ztyi == 6) {
						 dzij.ztyi = 0; break;
					 }
					 dzij.tyi = dzij.ztyi, dzij.tyj = 1;
				 }
			 }
			else if (input == 27) {
				gamestatus = 3;
			}
		}
	}
}
void gameover() {
	EndBatchDraw();
	_getch();
	closegraph();
}


