#include <memory>
#include "DxLib.h"
#include "GameCommon.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "RankingScene.h"

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

	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*Scene�̍쐬*/
	auto p_titleScene = std::make_unique<TitleScene>();
	auto p_gameScene = std::make_unique<GameScene>();
	auto p_rankingScene = std::make_unique<RankingScene>();

	/*�Q�[�����[�v��*/
	//Debug�ϐ�
	SceneKind firstScene = SceneKind::TITLESCENE;
	//Scene�ϐ�
	SceneKind nowScene = firstScene;
	SceneKind nextScene = firstScene;
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�Q�[��������*/
		if (nowScene == SceneKind::TITLESCENE)
		{
			//���o�͏���
			MyKeyInput::Update();//Keybord.
			MyMouseInput::Update();//Mouse.
			//�v�Z����
			nextScene = p_titleScene->Update();
			//�`�揈��
			p_titleScene->Draw();
			//Debug����
		}
		else if (nowScene == SceneKind::GAMESCENE)
		{
			//���o�͏���
			MyKeyInput::Update();//Keybord.
			MyMouseInput::Update();//Mouse.
			//�v�Z����
			nextScene = p_gameScene->Update();
			//�`�揈��
			p_gameScene->Draw();
			//Debug����
			p_gameScene->DebugDraw();
		}
		else if (nowScene == SceneKind::RANKING)
		{
			//���o�͏���
			MyKeyInput::Update();//Keybord.
			MyMouseInput::Update();//Mouse.
			//�v�Z����
			nextScene = p_rankingScene->Update();
			//�`�揈��
			p_rankingScene->Draw();
			//Debug����
			p_rankingScene->DebugDraw();
		}
		else if (nowScene == SceneKind::GAMEEND)
		{
			gameRoop = false;
		}

		/*Scene�ύX����������*/
		if (nextScene != nowScene)
		{
			//�V�[���؂�ւ�
			nowScene = nextScene;
			//���ꂼ��̃V�[���̏���������
			if (nowScene == SceneKind::TITLESCENE)
			{
				p_titleScene->Init();
			}
			else if(nowScene == SceneKind::GAMESCENE)
			{
				p_gameScene->Init();
			}
			else if (nowScene == SceneKind::RANKING)
			{
				p_rankingScene->Init();
			}
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