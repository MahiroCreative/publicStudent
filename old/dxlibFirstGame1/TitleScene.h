#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"

class TitleScene
{
private:
	SceneKind _nextScene, _tempScene;//�V�[���J�ڗp
	int _arrowY;
	int _countFrame;//�^�C�}�p
public:
	TitleScene() :
		_nextScene(SceneKind::TITLESCENE),
		_tempScene(SceneKind::TITLESCENE),
		_arrowY(480),
		_countFrame(0)
	{
	};
	/*�����o�֐�*/
	SceneKind Update()
	{
		/*��󑀍�*/
		//up.
		if(MyKeyInput::isDownKey(KEY_INPUT_UP))
		{
			if (_arrowY <= 480)
			{
				_arrowY = 560;//���ݒn����ԏ�Ȃ��ԉ��Ɉړ�
			}
			else
			{
				_arrowY -= 40;//40up.
			}

		}
		//down.
		if (MyKeyInput::isDownKey(KEY_INPUT_DOWN))
		{
			if (_arrowY >= 560)
			{
				_arrowY = 480;//���ݒn����ԉ��Ȃ��ԏ�Ɉړ�
			}
			else
			{
				_arrowY += 40;//40down.
			}
		}

		/*���菈��*/
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			if (_arrowY == 480)
			{
				_nextScene = SceneKind::GAMESCENE;
			}
			else if (_arrowY == 520)
			{
				_nextScene = SceneKind::RANKING;
			}
			else if (_arrowY == 560)
			{
				_nextScene = SceneKind::GAMEEND;
			}
		}

		/*�^�C�}�X�V*/
		_countFrame++;
		if (_countFrame > 80000) { _countFrame = 0; }//���ȏ㐔���������珉����(���͓K��)

		return _nextScene;
	}
	void Draw()
	{
		//�^�C�g���\��
		SetFontSize(80);//�t�H���g�T�C�Y�㏸
		DrawString(360, 240, "DxlibFirstGame", GetColor(255, 255, 255));

		//�{�^���\��
		SetFontSize(20);//�t�H���g�T�C�Y���f�t�H���g�ɖ߂�
		DrawString(600, 480, "GameStart", GetColor(255, 255, 255));
		DrawString(600, 520, "Ranking", GetColor(255, 255, 255));
		DrawString(600, 560, "END", GetColor(255, 255, 255));

		//���\��(�_�ł�����)
		if ((_countFrame % 60) < 32 )
		{
			DrawString(560, _arrowY, "=>", GetColor(255, 255, 255));
		}

	}
	/// <summary>
	/// �C���X�^���X�̏�����
	/// </summary>
	void Init()
	{
		_nextScene = SceneKind::TITLESCENE;
		_tempScene = SceneKind::TITLESCENE;
		_arrowY = 480;
		_countFrame = 0;
	}
};