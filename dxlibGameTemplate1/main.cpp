#include "DxLib.h"
#include <math.h>

/*�T�v*/
//����:DxlibGameTemplate1
//C����́w�֐��܂Łx�őg�񂾃e���v���[�g�ł��B
// ���ɊȈՓI�ł���
// �E�V�[���J��(�O���[�o���ϐ���if���Ŏ���)
// �E�C���v�b�g�V�X�e��(�O���[�o���ϐ��̗��p�ɂ�����)
// �E�~�̓����蔻��(�x�N�g�����g�킸�Ɏ���)
// �Ȃǂ�����Ă��܂��B
// �쐬����Q�[���̉��n�Ƃ��Ďg�����́w�ǂ�ŗ����ł��邩�H�x�Ŋw�K�i�x���m�F���Ă��������B
// ���ȏ���Dxlib�̃��t�@�����X�����Ȃ���̗����ō\���܂���B
// ������Ȃ��w����C�̊w�K����蒼���Ă��������B

/*�\��*/
//���ꂼ��̃V�[�����֐�(���\�b�h)�Ƃ��ĕ������āA
//���s���郁�\�b�h��؂�ւ��鎖�ŃV�[���Ǘ������Ă���B
//�V�[������̕Ԃ�l�Ŏ��ɂ����V�[���𔻒f���Ă��܂��B

/*����*/
//fps�̍��ɂ�鋓���̈Ⴂ�͍l�����Ă��܂���B
//���ɂ��A�I�u�W�F�N�g�̑��x�Ȃǂ��ς���Ă��܂��܂��B

/*�O���[�o���ϐ�*/
//�萔
constexpr int GAMEEND = 0;
constexpr int TITLESCENE = 1;
constexpr int GAMESCENE = 2;
//int�ϐ�
int MaxScore = 0;
//bool�ϐ�
bool isInputEnterHold = false;//InputEnter�p�̕ϐ�
bool isInputUpHold = false;//InputUp�p�̕ϐ�
bool isInputDownHold = false;//InputDown�p�̕ϐ�

/*�v���g�^�C�v�錾*/
//��`��Main�̉��B
int TitleScene();//�^�C�g���V�[��
int GameScene();//�Q�[���V�[��
bool InputEnter();//Enter�������ꂽ���ǂ����𔻒肷��֐�
bool InputUp();//Up�������ꂽ���ǂ����𔻒肷��֐�
bool InputDown();//Down�������ꂽ���ǂ����𔻒肷��֐�


//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*�萔*/
	//��ʃT�C�Y
	constexpr int ScreenSizeX = 1280;//��
	constexpr int ScreenSizeY = 720;//����

	/*�ϐ�*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;
	int nextScene = TITLESCENE;

	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�Q�[�����[�v��*/
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�Q�[��������*/
		//�V�[���Ǘ�
		if (nextScene == TITLESCENE)
		{
			nextScene = TitleScene();
		}
		else if (nextScene == GAMESCENE)
		{

			nextScene = GameScene();
		}
		else if (nextScene == GAMEEND)
		{
			break;
		}

		//����ʂ�\��
		ScreenFlip();

		//���t���b�V������(-1�Ȃ�G���[)
		if (ProcessMessage() < 0) { break; }

		//���[�v�I������
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }

		//fps�Œ�(60fps:16.66ms)
		//���[�v�J�n��������16.66ms�o�܂Œ�~
		while (GetNowHiPerformanceCount() - roopStartTime < 16667) {}
	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}

/*�V�[����`*/
//�^�C�g����ʂ����s����V�[���B
//�Ԃ�l�Ŏ��Ɏ��s����V�[�����w�肷��B
int TitleScene()
{
	/*�ϐ�*/
	bool gameRoop = true;
	int nextScene = TITLESCENE;
	int arrowPosY = 440;
	int countFrame = 0;

	/*�Q�[������*/
	while (gameRoop)
	{
		/*�v�Z����*/
		//Input Down.
		if (InputDown())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}


		/*�^�C�}�X�V*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//���ȏ㐔���������珉����(���͓K��)

		/*Draw����*/
		//����ʂ̏�����
		ClearDrawScreen();

		//�^�C�g�����S
		SetFontSize(80);//�t�H���g�T�C�Y�ύX
		DrawString(440, 240, "DxlibGame", GetColor(255, 255, 255));
		SetFontSize(40);//�t�H���g�T�C�Y��
		DrawString(460, 320, "-GameTemplate1-", GetColor(255, 255, 255));
		SetFontSize(20);//�t�H���g�T�C�Y������
		//�Q�[���V�[���e�L�X�g
		DrawString(600, 440, "START", GetColor(255, 255, 255));
		//�Q�[���G���h�e�L�X�g
		DrawString(600, 480, "END", GetColor(255, 255, 255));
		//���\��(�_�ł�����)
		if ((countFrame % 60) < 32)
		{
			DrawString(560, arrowPosY, "->", GetColor(255, 255, 255));
		}



		/*DebugDraw����*/
		DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//�V�[�����\��

		//����ʂ�\��
		ScreenFlip();

		/*�V�[���J�ڏ���*/
		//�G���^�[�ŃV�[���ύX
		if (InputEnter())
		{
			if (arrowPosY == 440)
			{
				return GAMESCENE;
			}
			else
			{
				return GAMEEND;
			}

		}
	}

	//��O����
	return TITLESCENE;
}
//�Q�[����ʂ����s����V�[���B
//�Ԃ�l�Ŏ��Ɏ��s����V�[�����w�肷��B
int GameScene()
{
	/*�ϐ�*/
	bool gameRoop = true;
	bool isShot = false;
	bool isEnemyShot = false;
	bool isHitEnemy = false;
	bool isHitPlayer = false;
	int nextScene = GAMESCENE;
	int playerHandle = LoadGraph("Chara.png");
	int playerPosX = 100;
	int playerPosY = 300;
	int playerColR = 14;
	int enemyPosX = 1200;
	int enemyPosY = 360;
	int enemyColR = 240;
	int bulletPosX = playerPosX;
	int bulletPosY = playerPosY;
	int bulletR = 8;
	int enemyBulletPosX = enemyPosX;
	int enemyBulletPosY = enemyPosY;
	int enemyBulletR = 64;
	int playerSpeed = 3;
	int bulletSpeed = 8;
	int enemyBulletSpeed = 3;
	int enemySpeed = 1;
	int score = 0;

	/*�Q�[������*/
	while (gameRoop)
	{
		/*player����*/
		playerPosY -= CheckHitKey(KEY_INPUT_W) * playerSpeed;//up
		playerPosY += CheckHitKey(KEY_INPUT_S) * playerSpeed;//down
		playerPosX += CheckHitKey(KEY_INPUT_D) * playerSpeed;//right.
		playerPosX -= CheckHitKey(KEY_INPUT_A) * playerSpeed;//left.
		//bullet����
		if (isShot == false)
		{
			if (GetMouseInput() == MOUSE_INPUT_LEFT) isShot = true;
		}

		/*playerBullet�̓���*/
		//bullet�ʒu�X�V
		if (isShot)
		{
			bulletPosX = bulletPosX + bulletSpeed;
		}
		else
		{
			bulletPosX = playerPosX;
			bulletPosY = playerPosY;
		}
		//��ʒ[��bullet�ʒu������
		if (bulletPosX > 1280)
		{
			isShot = false;
			bulletPosX = playerPosX;
			bulletPosY = playerPosY;
		}

		/*�G�l�~�[����*/
		//�G�l�~�[�ʒu�X�V
		enemyPosY += enemySpeed;
		//���]
		if (enemyPosY > 560)
		{
			enemySpeed = -enemySpeed;
		}
		else if (enemyPosY < 160)
		{
			enemySpeed = -enemySpeed;
		}
		//enemyBullet����
		if (isEnemyShot == false)
		{
			if (enemyPosY % 3 == 0) isEnemyShot = true;
		}

		/*enemyBullet*/
		//enemyBullet�̓���
		if (isEnemyShot)
		{
			enemyBulletPosX = enemyBulletPosX - enemyBulletSpeed;
		}
		else
		{
			enemyBulletPosX = enemyPosX;
			enemyBulletPosY = enemyPosY;
		}
		//enemyBullet�ʒu������
		if (enemyBulletPosX < -enemyBulletR * 2)
		{
			isEnemyShot = false;
			enemyBulletPosX = enemyPosX;
			enemyBulletPosY = enemyPosY;
			//enemyBulletSpeed�̍X�V
			enemyBulletSpeed++;
		}

		/*�����蔻��*/
		//enemy
		int delX = bulletPosX - enemyPosX;
		int delY = bulletPosY - enemyPosY;
		int Length = (int)sqrt(delX * delX + delY * delY);//�G�l�~�[�ƒe�̋���
		if (bulletR + enemyColR > Length)
		{
			isHitEnemy = true;
		}
		else
		{
			isHitEnemy = false;
		}
		//player
		delX = enemyBulletPosX - playerPosX;
		delY = enemyBulletPosY - playerPosY;
		Length = (int)sqrt(delX * delX + delY * delY);//�v���C���[�ƒe�̋���
		if (enemyBulletR + playerColR > Length)
		{
			isHitPlayer = true;
		}

		/*�X�R�A�̍X�V*/
		if (isHitEnemy)
		{
			score++;
		}

		/*Draw����*/
		//����ʂ̏�����
		ClearDrawScreen();

		//player
		DrawRotaGraph(playerPosX, playerPosY, 1, 0, playerHandle, true);//�w�肵���ʒu�ɉ摜�̒��S������
		//bullet.
		if (isShot)
		{
			DrawCircle(bulletPosX, bulletPosY, bulletR, GetColor(255, 0, 0), 1);
		}
		//enemy
		if (isHitEnemy)
		{
			DrawCircle(enemyPosX, enemyPosY, 240, GetColor(0, 255, 255), 1);
		}
		else
		{
			DrawCircle(enemyPosX, enemyPosY, 240, GetColor(0, 0, 255), 1);
		}
		//enemyBullet
		if (isEnemyShot)
		{
			DrawCircle(enemyBulletPosX, enemyBulletPosY, enemyBulletR, GetColor(255, 0, 0), 1);
		}
		//score
		DrawFormatString(10, 700, GetColor(0, 255, 255), "Score:%d", score);
		//MaxScore
		DrawFormatString(1100, 0, GetColor(255, 255, 255), "MaxScore:%d", MaxScore);

		/*DebugDraw����*/
		DrawString(0, 0, "GameScene�FWASD�ő���EEnter�Ń^�C�g��", GetColor(255, 255, 255));//�V�[�����\��
		DrawCircle(playerPosX, playerPosY, playerColR, GetColor(0, 255, 0), 0);//PlayerCol
		DrawCircle(enemyPosX, enemyPosY, enemyColR, GetColor(0, 255, 0), 0);//enemyCol
		DrawCircle(enemyBulletPosX, enemyBulletPosY, enemyBulletR, GetColor(0, 255, 0), 0);//enemyCol

		//����ʂ�\��
		ScreenFlip();

		/*�V�[���J�ڏ���*/
		//�G���^�[�ŃV�[���ύX
		if (InputEnter())
		{
			return TITLESCENE;
		}
		if (isHitPlayer)
		{
			//�X�R�A�̍X�V
			if (score > MaxScore)
			{
				MaxScore = score;
			}
			return TITLESCENE;
		}

	}

	//��O����
	return TITLESCENE;
}

/*Input�֐�*/
//Enter�������ꂽ���ǂ����𔻒肷��֐�
//Enter���������炸�C�P�ĂȂ��B���R�����蒼���Ă����܂��B
bool InputEnter()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_RETURN) && !isInputEnterHold)
	{
		isInputEnterHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		isInputEnterHold = false;
	}

	return false;
}
//Up�������ꂽ���ǂ����𔻒肷��֐�
//Up���������炸�C�P�ĂȂ��B���R�����蒼���Ă����܂��B
bool InputUp()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_UP) && !isInputDownHold)
	{
		isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_UP))
	{
		isInputDownHold = false;
	}

	return false;
}
//Down�������ꂽ���ǂ����𔻒肷��֐�
//Down���������炸�C�P�ĂȂ��B���R�����蒼���Ă����܂��B
bool InputDown()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_DOWN) && !isInputUpHold)
	{
		isInputUpHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_DOWN))
	{
		isInputUpHold = false;
	}

	return false;
}