#include "DxLib.h"
#include <iostream>
#include<string>
using namespace std;

/*�쐬�����֐�*/
//Http�ʐM��Get���߂��o���A���̌��ʂ𓾂�B
string HttpGet(const char* Domain, const char* URI);

/*�w���ւ̒��ӓ_*/
//�y�l�b�g���[�N�ʐM���s����ŕK�v�Ȓm���z
// �ETCP/IP
// �EHTTP�ʐM
// �ESQL
// �EPHP
// ��L�S���A�����Œ��ׂāw��̂Ȃɂ��H�x���炢�͕������Ă����܂��傤�B
// ����HTTP�ʐM�Ɋւ��Ă͂������蒲�ׂ�K�v������܂��B
// 
//�yDxLib�̕��ŕK�v�Ȓm���z
//Dxlib�̒ʐM�֌W�͐��������ĕn��ł��B
//winsock�Ƃ������Â�API���������Ďg���Ă���A���Ȃ茴�n�I�ł��B
//���̂��߁A�C���^�[�l�b�g���o�R�����ʐM���s���ɂ̓��t�@�����X�ɍڂ��Ă���֐��ł͑���܂���B
//����J�֐�(�ꉞ�g���邪�������̂���)���g���K�v������܂��B
//�wdx���C�u�����B���֐��x�Ō������āw�����������̂�����x�ƒm��܂��傤�B
// 
//�y����̃R�[�h�Ɋւ��āz
//�����\���ƒT���Ă��邾���̂�������؃R�[�h�ł��B
//�w�����\�Ȃ炱��ł��ǂ��ł����A���p���x���̎������Ɩ�肾�炯�ł��B
//�w�K�p�̃R�[�h���Ǝv���A�s���葽���Ɍ��J����悤�ȕ������ۂɂ͗��p����͎̂~�߂܂��傤�B


/*Main*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//window���[�h
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;
	}

	/*Http�ʐM��Get���߂��w��̃A�h���X�ɍs���Ă���*/
	//�����L���O�̍X�V
	string  ans1 = HttpGet("mahiro.punyu.jp", "/test/ranking/updateRanking.php?name=testName&score=78");
	//��ʃN���A
	ClearDrawScreen();
	//�����L���O�̎擾
	string  ans2 = HttpGet("mahiro.punyu.jp", "/test/ranking/getRanking.php");


	WaitKey();// �L�[���͑҂�
	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return 0;// �\�t�g�̏I�� 
}


/// <summary>
/// Http�ʐM�ł�Get���߂𑗂鎖���ł��閽��
/// </summary>
/// <param name="Domain">Domain�������</param>
/// <param name="URI">URI�����</param>
/// <returns>string�^�Ŏ��s���ʂ𓾂�(�\��ł܂�����Ă܂���)</returns>
string HttpGet(const char* Domain, const char* URI)
{
	/*�K���ȕϐ�*/
	string ans;
	int i = 12;//�����̕\���ʒu�p

	/*�����֌W*/
	unsigned int Cr = GetColor(255, 255, 255);	 // ���F�̒l���擾
	SetFontSize(12);                             //�T�C�Y�ύX
	SetFontThickness(4);                         //������ύX

	/*�l�b�g���[�N�p�̕ϐ�*/
	const int DATA_SIZE = 2560;//8bit�̂ł�����(char�ő�v�f����268435455)
	char StrBuf[DATA_SIZE] = "";    // �f�[�^�o�b�t�@
	IPDATA Ip;        // �ڑ��p�h�o�A�h���X�f�[�^
	int NetHandle;        // �l�b�g���[�N�n���h��
	int DataLength;        // ��M�f�[�^�ʕۑ��p�ϐ�

	/*Http�ʐM���쐬���邽�߂̕ϐ�*/
	char HttpCmd[128] = "";

	//DxLib�̗]�v�ȋ@�\��؂�B
	SetUseDXNetWorkProtocol(false);

	//DNS����h���C������IP�A�h���X�擾
	int test = GetHostIPbyName(Domain, &Ip);
	DrawFormatString(0, 0, Cr, "GetDomain:%d", test);//0�Ȃ琳��

	//�擾����IP�A�h���X�̊m�F
	DrawFormatString(0, i, Cr, "IpAdress;%d,%d,%d,%d", Ip.d1, Ip.d2, Ip.d3, Ip.d4);

	// �ʐM���m��
	NetHandle = ConnectNetWork(Ip, 80);
	DrawFormatString(0, i * 2, Cr, "NetHandle:%d", NetHandle);

	// �m�������������ꍇ�̂ݒ��̏���������
	if (NetHandle != -1)
	{
		//Http���߂̍쐬
		sprintf_s(HttpCmd, "GET %s HTTP/1.1\nHost: %s\n\n", URI, Domain);
		DrawFormatString(0, i*3, Cr, "HttpCmd:\n%s", HttpCmd);


		// �f�[�^���M(http���߂𑗂�)
		NetWorkSend(NetHandle, HttpCmd, strlen(HttpCmd));

		// �f�[�^������̂�҂�
		while (!ProcessMessage())
		{
			// �擾���Ă��Ȃ���M�f�[�^�ʂ𓾂�
			DataLength = GetNetWorkDataLength(NetHandle);

			// �擾���ĂȂ���M�f�[�^�ʂ�-1����Ȃ��ꍇ�̓��[�v�𔲂���
			if (DataLength != -1)
			{
				break;
			}
		}

		// �f�[�^��M
		NetWorkRecv(NetHandle, StrBuf, DATA_SIZE);    // �f�[�^���o�b�t�@�Ɏ擾

		// ��M�����f�[�^��`��
		DrawString(0, i * 8, StrBuf, GetColor(255, 255, 255));

		// �L�[���͑҂�
		WaitKey();

		// �ڑ���f��
		CloseNetWork(NetHandle);
	}

	return ans;
}