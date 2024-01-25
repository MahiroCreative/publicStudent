#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"
#include "RankingScene.h"


class GameScene
{
private:
	/*�����o�ϐ�*/
	SceneKind _nextScene;//�V�[���X�V�p
	IntVector _charaPos;//�L�����N�^�̈ʒu
	IntVector _charaColPos;//�L�����N�^�̃R���W�����̈ʒu
	IntVector _enemyPos;//�G�l�~�[�̈ʒu
	IntVector _shotPos;//�V���b�g�̈ʒu
	IntVector _bulletPos;//�e�ۂ̈ʒu
	IntVector _bullet2Pos;//�e�ۂ̈ʒu
	IntVector _bullet3Pos;//�e�ۂ̈ʒu
	IntVector _bullet4Pos;//�e�ۂ̈ʒu
	IntVector _bullet5Pos;//�e�ۂ̈ʒu
	int _charaHandle;//�L�����̉摜�n���h��
	int _charaSpeed;//�L�����̈ړ����x
	int _charaColR;//�L�����R���W�����̔��a
	int _enemyR;//�G�l�~�[�̔��a
	int _bulletColR;//�e�ۃR���W�����̔��a
	int _debugInt;//Debug�p
	int _bulletSpeed;
	int _shotR;
	int _debug;
	int _score;
	bool _isHitFlag;//�����蔻��t���O
	bool _isEnemyHitFlag;
	bool _isShotFlag;
public:
	/*�R���X�g���N�^*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE),
		_charaPos(80, 360),
		_charaColPos(_charaPos.X + 23, _charaPos.Y + 20),
		_charaColR(16),
		_charaHandle(-1),
		_charaSpeed(4),
		_enemyPos(1280,360),
		_enemyR(240),
		_shotPos(_charaPos.X, _charaPos.Y + 20),
		_bulletPos(800, 120),
		_bullet2Pos(800, 240),
		_bullet3Pos(800, 360),
		_bullet4Pos(800, 480),
		_bullet5Pos(800, 600),
		_bulletColR(8),
		_bulletSpeed(4),
		_shotR(8),
		_debug(0),
		_score(0),
		_isHitFlag(false),
		_isEnemyHitFlag(false),
		_isShotFlag(false)
	{
		_charaHandle = LoadGraph("Chara.png");
	};
	/*�����o�֐�*/
	//�����̍X�V
	SceneKind Update()
	{

		/*�L�����X�V*/
		//�ړ�����
		//up.
		if (MyKeyInput::isHoldKey(KEY_INPUT_W) && _charaPos.Y > 0)
		{
			_charaPos.Y -= _charaSpeed;
		}
		//down.
		if (MyKeyInput::isHoldKey(KEY_INPUT_S) && _charaPos.Y < 680)
		{
			_charaPos.Y += _charaSpeed;
		}
		//left.
		if (MyKeyInput::isHoldKey(KEY_INPUT_A))
		{
			_charaPos.X -= _charaSpeed;
		}
		//right.
		if (MyKeyInput::isHoldKey(KEY_INPUT_D))
		{
			_charaPos.X += _charaSpeed;
		}
		//�R���W�����ʒu�̍X�V
		_charaColPos.X = _charaPos.X + 23;
		_charaColPos.Y = _charaPos.Y + 20;

		/*�e�ۍX�V*/
		//�e��1:�ړ�
		_bulletPos.X -= _bulletSpeed;
		//�e��2:�ړ�
		_bullet2Pos.X -= _bulletSpeed;
		//�e��3:�ړ�
		_bullet3Pos.X -= _bulletSpeed;
		//�e��4:�ړ�
		_bullet4Pos.X -= _bulletSpeed;
		//�e��5:�ړ�
		_bullet5Pos.X -= _bulletSpeed;

		/*�e�ۂ̏�����*/
		if (_bulletPos.X < 0)
		{
			//1.
			_bulletPos.X = 1100;
			_bulletPos.Y = rand() % 240;
			//2.
			_bullet2Pos.X = 1100;
			_bullet2Pos.Y = rand() % 120 + 120;
			//3
			_bullet3Pos.X = 1100;
			_bullet3Pos.Y = rand() % 240 + 240;
			//4.
			_bullet4Pos.X = 1100;
			_bullet4Pos.Y = rand() % 360 + 360;
			//5.
			_bullet5Pos.X = 1100;
			_bullet5Pos.Y = rand() % 240 + 480;
			//�e�ۑ��x�X�V
			_bulletSpeed += 2;
		}

		/*�L���������蔻��*/
		//�e��1�Ƃ̓����蔻��v�Z
		int HitLength = _charaColR + _bulletColR;//���ʕ�
		IntVector delVec = _charaColPos - _bulletPos;
		int delLength = delVec.Length();
		//�e��2�Ƃ̓����蔻��v�Z
		IntVector delVec2 = _charaColPos - _bullet2Pos;
		int delLength2 = delVec2.Length();
		//�e��3�Ƃ̓����蔻��v�Z
		IntVector delVec3 = _charaColPos - _bullet3Pos;
		int delLength3 = delVec3.Length();
		//�e��4�Ƃ̓����蔻��v�Z
		IntVector delVec4 = _charaColPos - _bullet4Pos;
		int delLength4 = delVec4.Length();
		//�e��5�Ƃ̓����蔻��v�Z
		IntVector delVec5 = _charaColPos - _bullet5Pos;
		int delLength5 = delVec5.Length();
		//����
		if (HitLength > delLength)
		{
			_isHitFlag = true;
		}
		else if (HitLength > delLength2)//�e�ۂQ
		{
			_isHitFlag = true;
		}
		else if (HitLength > delLength3)//�e�ۂR
		{
			_isHitFlag = true;
		}
		else if (HitLength > delLength4)//�e�ۂS
		{
			_isHitFlag = true;
		}
		else if (HitLength > delLength5)//�e��5
		{
			_isHitFlag = true;
		}
		else
		{
			_isHitFlag = false;
		}

		/*�V���b�g*/
		if (MyMouseInput::isHoldKey(MOUSE_INPUT_LEFT))//�N���b�N���͗��߂�
		{
			_isShotFlag = true;
		}
		//�ړ�
		if (_shotPos.X > 1280)
		{
			_shotPos = _charaPos;
			_isShotFlag = false;
		}
		else if(_isShotFlag)
		{
			_shotPos.X += 16;
		}

		/*�V���b�g�ƓG�̓����蔻��*/
		int HitLengthEnemy = _shotR + _enemyR;
		IntVector delVecEnemy = _shotPos - _enemyPos;
		int delEnemyLength = delVecEnemy.Length();
		if (HitLengthEnemy > delEnemyLength)
		{
			_isEnemyHitFlag = true;
			_score++;
		}
		else
		{
			_isEnemyHitFlag = false;
		}

		/*�V�[���J�ڏ���*/
		//Enter�L�[����������Title�V�[���ɑJ��
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}
		//�G�Ɠ������Ă�����^�C�g����ʂցB
		if (_isHitFlag)
		{
			if (RankingScene::_maxScore < _score)
			{
				RankingScene::_maxScore = _score;
			}

			_nextScene = SceneKind::TITLESCENE;
		}

		return _nextScene;
	}
	//�`��X�V
	void Draw()
	{
		//�L�����N�^�[�̕`��
		DrawGraph(_charaPos.X, _charaPos.Y, _charaHandle, TRUE);

		//�G�l�~�[�̕`��
		if (_isEnemyHitFlag)
		{
			DrawCircle(_enemyPos.X, _enemyPos.Y, _enemyR, GetColor(0, 155, 155), 1);

		}
		else
		{
			DrawCircle(_enemyPos.X, _enemyPos.Y, _enemyR, GetColor(255, 255, 255), 1);
		}


		//�e�ۂ̕`��
		DrawCircle(_bulletPos.X, _bulletPos.Y, 8, GetColor(255, 0, 0), 1);
		DrawCircle(_bullet2Pos.X, _bullet2Pos.Y, 8, GetColor(255, 0, 0), 1);
		DrawCircle(_bullet3Pos.X, _bullet3Pos.Y, 8, GetColor(255, 0, 0), 1);
		DrawCircle(_bullet4Pos.X, _bullet4Pos.Y, 8, GetColor(255, 0, 0), 1);
		DrawCircle(_bullet5Pos.X, _bullet5Pos.Y, 8, GetColor(255, 0, 0), 1);

		//�V���b�g�̕`��
		if (_isShotFlag)
		{
			DrawCircle(_shotPos.X, _shotPos.Y, 8, GetColor(0, 0, 255), 1);
		}

	}
	//�f�o�b�O�p�̕`��X�V
	void DebugDraw()
	{
		//���݂̃V�[������`��
		DrawString(8, 8, "SceneName:GameScene", GetColor(0, 255, 255));

		//�L�����N�^�[�̃R���W�����̕`��
		DrawCircle(_charaColPos.X, _charaColPos.Y, _charaColR, GetColor(0, 255, 255), 0);

		//�e�ۂ̃R���W�����̕`��
		DrawCircle(_bulletPos.X, _bulletPos.Y, _bulletColR, GetColor(0, 255, 255), 0);
		DrawCircle(_bullet2Pos.X, _bullet2Pos.Y, _bulletColR, GetColor(0, 255, 255), 0);
		DrawCircle(_bullet3Pos.X, _bullet3Pos.Y, _bulletColR, GetColor(0, 255, 255), 0);
		DrawCircle(_bullet4Pos.X, _bullet4Pos.Y, _bulletColR, GetColor(0, 255, 255), 0);
		DrawCircle(_bullet5Pos.X, _bullet5Pos.Y, _bulletColR, GetColor(0, 255, 255), 0);

		//DebugNum
		DrawFormatString(10, 700, GetColor(0, 255, 255), "Score:%d", _score);
	}
	/// <summary>
	/// �C���X�^���X�̏�����
	/// </summary>
	void Init()
	{
		//�����o�ϐ��̏�����
		_nextScene = SceneKind::GAMESCENE;

		//�e�ۏ�����
		//1.
		_bulletPos.X = 1100;
		_bulletPos.Y = 120;
		//2.
		_bullet2Pos.X = 1100;
		_bullet2Pos.Y = 240;
		//3
		_bullet3Pos.X = 1100;
		_bullet3Pos.Y = 360;
		//4.
		_bullet4Pos.X = 1100;
		_bullet4Pos.Y = 480;
		//5.
		_bullet5Pos.X = 1100;
		_bullet5Pos.Y = 600;

		//�e�ۑ��x�̏�����
		_bulletSpeed = 4;

		//score������
		_score = 0;
	}
};