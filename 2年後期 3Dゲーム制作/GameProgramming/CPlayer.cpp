//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
#include"CGoal.h"
#include"CBlock.h"
#include"CKey.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CText.h"
#include"CUtil.h"
#include"CInput.h"
#include"CSound.h"
#include"CSceneGame.h"

#define GLAVITY -0.07f //�d��
#define JUMPPOWER 3.0f	//�W�����v��
#define JUMPRECHARGE 70	//���W�����v�܂ł̑҂�����

#define STEPSPEED 17
#define STEPMOVE 5
#define STEPRECHARGE 120

#define VELOCITY 0.065f	//�ړ���
#define SPEEDREMIT 0.9	//���x����
#define SUBERI 2	//����Ղ�

#define RELOAD -80

#define PHP 5	//HP

#define MOUSESPEEDX 1.2f	//�}�E�X�����x
#define MOUSESPEEDY 1.2f	//�}�E�X�c���x

int CPlayer::mPlayerHp = PHP;

float CPlayer::mSpeedX = NULL;
float CPlayer::mSpeedY = NULL;
float CPlayer::mSpeedZ = NULL;

CText mText;

int CPlayer::mScore;

float CPlayer::mTime;

//����
extern CSound Fire;
extern CSound Reloaded;
extern CSound Bomb;
extern CSound Jump;
extern CSound Step;
extern CSound Faild;
extern CSound Moving;


CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -6.0f), CVector(0.0f, 0.0f, 6.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 8.0f, 0.0f), CVector(0.0f, -8.0f, 0.0f))
, mLine3(this, &mMatrix, CVector(6.0f, 0.0f, 0.0f), CVector(-6.0f, 0.0f, 0.0f))
, mCollider(this, &mMatrix, CVector(0.0f,0.0f,0.0f),3.5f)
, mSearchLine(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 80.0f))
{
	mText.LoadTexture("FontWhite.tga", 1, 64);
	CCharacter::mTag = EPLAYER; //�^�O�̐ݒ�
	
	mJumpTimer = 0;
	mJump = true;

	mTimeCount = true;

	mStep = -1;
	mStepRecharge = 0;

	mReloadTime = 0;
	mNotHit = 0;

	mTime = 0;
	mScore = 0;

	mFaildSound = true;


	mBeforMouseX = 0;
	mBeforMouseY = 0;
	mMouseMoveX = 0;
	mMouseMoveY = 0;

	mMouseSpeedX = MOUSESPEEDX;
	mMouseSpeedY = MOUSESPEEDY;

	mSearchLine.mTag = CCollider::ESEARCH;
}

//�X�V����
void CPlayer::Update() {
	if (mPosition.mY < 0) {
		mPosition.mY = 0.1f;
	}

	//CTransform�̍X�V
	CTransform::Update();


	if (mPlayerHp > 0) {
		if (CSceneGame::mStartFlag == false) {	//�X�^�[�g�O�̍s������

			//���ԉ��Z
			if (CGoal::mTouchGoal == false) {
				mTime++;
			}

			//shift�L�[�Ń_�b�V��
			if (CKey::Push(VK_SHIFT) && mSpeedZ < SPEEDREMIT + 3.0f) {
				if (CKey::Push('W'))
					mSpeedZ += VELOCITY + 0.4f;
				Moving.Play();
			}

			//�ړ�
			if (CKey::Push('W') && mSpeedZ < SPEEDREMIT + 1.1f) {
				//Z����+�ړ�
				mSpeedZ += VELOCITY + 0.2f;
				Moving.Play();
			}
			if (CKey::Push('S') && mSpeedZ > -SPEEDREMIT - 0.3f) {
				//Z����-�ړ�
				mSpeedZ -= VELOCITY;
				Moving.Play();
			}
			if (CKey::Push('A') && mSpeedX < SPEEDREMIT) {
				//X����+�ړ�
				mSpeedX += VELOCITY;
				Moving.Play();
			}
			if (CKey::Push('D') && mSpeedX > -SPEEDREMIT) {
				//X����-�ړ�
				mSpeedX -= VELOCITY;
				Moving.Play();
			}


			//�X�y�[�X�L�[�ŃW�����v
			if (CKey::Once(VK_SPACE) && mJump == true) {
				mSpeedY = JUMPPOWER;
				mJumpTimer = JUMPRECHARGE;
				Jump.Play();
				mJump = false;
			}

			////�ꎞ�I����L�[
			//if (CKey::Push(VK_RIGHT)) {
			//	mRotation.mY -= 1;
			//}
			//if (CKey::Push(VK_LEFT)) {
			//	mRotation.mY += 1;
			//}

			//if (CKey::Push(VK_UP)) {
			//	mRotation.mX -= 1;
			//}
			//if (CKey::Push(VK_DOWN)) {
			//	mRotation.mX += 1;
			//}

			//��������}�E�X�ɂ�鑀��
			//���N���b�N�Œe�𔭎�
			if (CKey::Once(VK_LBUTTON) && mReloadTime > 0) {
				CBullet* bullet = new CBullet();
				bullet->mTag = CCharacter::EBULLET;
				bullet->Set(1.5f, 14.0f);
				bullet->mPosition = CVector(-3.0f, 3.0f, 10.0f) * mMatrix;
				bullet->mRotation = mRotation;
				bullet->Update();
				Fire.Play();
				mReloadTime = RELOAD;
			}
			if (mReloadTime < 1) {
				mReloadTime++;
			}
			if (mReloadTime == 0) {
				Reloaded.Play();
			}

			//�E�N���b�N�ŏu�Ԉړ�
			if (CKey::Once(VK_RBUTTON) && mStepRecharge < 0) {
				mStep = STEPMOVE;
				Step.Play();
				mStepRecharge = 60;
			}
			if (mStep > 0) {
				mSpeedZ += STEPSPEED;
			}
			if (mStep <= 0 && mStep >= -5 && mSpeedZ > 0.2f) {
				mSpeedZ -= 14.0f;
			}
			mStep--;
			mStepRecharge--;
		}	//�����܂ł��X�^�[�g�O�̓��쐧����

			//���_�㉺�p����
			if (mRotation.mX < -80)
				mRotation.mX = -79;

			if (mRotation.mX > 75)
				mRotation.mX = 74;


			//�}�E�X�ݒ�
			float mMousePosX, mMousePosY;	//�}�E�X�J�[�\�����W�擾�p
			//�}�E�X�J�[�\�����W�̎擾
			CInput::GetMousePos(&mMousePosX, &mMousePosY);

			//�Q�[����ʒ��S����̍��W�֕ϊ�
			mMousePosX -= 400;
			mMousePosY = 300 - mMousePosY;

			//�}�E�X�̈ړ���
			mMouseMoveX = mMousePosX - mBeforMouseX;
			mMouseMoveY = mMousePosY - mBeforMouseY;

			//���_����
			mRotation.mX -= mMouseMoveY / mMouseSpeedX;
			mRotation.mY -= mMouseMoveX / mMouseSpeedY;

			mBeforMouseX = mMousePosX;
			mBeforMouseY = mMousePosY;

			//�����܂Ń}�E�X�̑���
		}
	else {
		if (mFaildSound == true) {
			Faild.Play();
			mFaildSound = false;
		}
	}

	//�ʒu�̈ړ�
	mPosition = CVector(mSpeedX, 0.0f, mSpeedZ) * mMatrix;
	//�d��
	mSpeedY += GLAVITY;
	mPosition.mY += mSpeedY;

	//�����[��
		//X
	if (mSpeedX >= 0.01) {
		mSpeedX -= VELOCITY / SUBERI;
	}
	else if (mSpeedX <= -0.01) {
		mSpeedX += VELOCITY / SUBERI;
	}
	//Z
	if (mSpeedZ >= 0.01) {
		mSpeedZ -= VELOCITY / SUBERI;
	}
	else if (mSpeedZ <= -0.01) {
		mSpeedZ += VELOCITY / SUBERI;
	}


	if (mJumpTimer >= 0)
		mJumpTimer--;

	//���G���Ԍ��Z
	mNotHit--;

}

//�ڐG����
void CPlayer::Collision(CCollider *m, CCollider *o){
	//���g�̃R���C�_�^�C�v�Ŕ���
	switch (m->CCollider::mType) {
	case CCollider::ESPHERE:
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;		//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			CCollider::CollisionTriangleSphere(o, m, &adjust);
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition - adjust * -1;

			if (mPosition.mY < 2.0f) {
				//�W�����v�Ďg�p
				if (mJumpTimer < 0) {
					mJump = true;
				}
				//���n
				if (mPosition.mY < 1.0f && mSpeedY < 0) {
					mSpeedY += 0.009f;
				}
			}
			CTransform::Update();
		}

		//�_���[�W�u���b�N�ڐG��
		if(CCollider::Collision(m,o)){
			if (o->mpParent->mTag == EDAMAGEBLOCK) {
				if (mNotHit < 0) {
					mPlayerHp--;
				}
					mNotHit = 30;
					new CEffect(o->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
					Bomb.Play();
					o->mpParent->mEnabled = false;
				
			}
		}
		break;

	case CCollider::ELINE:
		if (o->mpParent != nullptr) {
			if (o->mType == CCollider::ETRIANGLE) {
				if (o->mpParent->mTag == EBLOCK || o->mpParent->mTag == EMOVEBLOCK) {
					if (mSpeedY < -4.0) {
						mSpeedY += 0.005f;
					}
					if (mJumpTimer < 0) {
						mJump = true;
					}
					break;
				}
			}
			if (m->mTag == CCollider::ESEARCH) {
					CVector adjust;		//�����p�x�N�g��
					//�O�p�`�Ɛ����̏Փ˔���
					CCollider::CollisionTriangleSphere(o, m, &adjust);


			}
		}

	}


}

//��ʏ�2D�`��
void CPlayer::Render(){
	//�e�̕`�揈��
	CCharacter::Render();

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�
	glColor4f(0.1f, 0.8f, 0.1f, 1.0f);
	//������ҏW�G���A�̍쐬
	char buf[64];

	//���x�\��
	//������̐ݒ�
	sprintf(buf, "PY:%5f", mPosition.mY);
	//������̕`��
	mText.DrawString(buf, -300, 200, 8, 16);

	//���x�\��
	//������̐ݒ�
	//sprintf(buf, "VX:%f", mSpeedX);
	//������̕`��
	//mText.DrawString(buf, -300, 200, 8, 16);

	//������̐ݒ�
	sprintf(buf, "VY:%f", mSpeedY);
	//������̕`��
	mText.DrawString(buf, -300, 150, 8, 16);

	//������̐ݒ�
	sprintf(buf, "VZ:%f", mSpeedZ);
	//������̕`��
	mText.DrawString(buf, -300, 100, 8, 16);




	//HP�\��
	sprintf(buf, "HP:", mPlayerHp);
	mText.DrawString(buf, -350, -250, 20, 20);

	for (int h = 0; mPlayerHp > h; h++) {
		sprintf(buf, "I");
		mText.DrawString(buf, (-250 + (h * 20)), -250, 20, 20);
	}

	//�X�R�A
	sprintf(buf, "SCORE:%d",mScore);
	mText.DrawString(buf, 150, 250, 13, 13);

	sprintf(buf, "TIME:%5.1f", mTime/60);
	mText.DrawString(buf, 100, 210, 13, 13);


	//�����[�h��
	if (mReloadTime < 0) {
		sprintf(buf, ":RELOADING");
		mText.DrawString(buf, 150, -220, 10, 10);

		for (int r = -80; mReloadTime > r; r += 20) {
			sprintf(buf, "[]");
			mText.DrawString(buf, 40 - r, -220, 12, 12);
		}
	}

	//�X�^�[�g�O
	if (CSceneGame::mStartFlag == true) {
		sprintf(buf, "READY");
		mText.DrawString(buf, -130, 0, 35, 35);
		sprintf(buf, "START TO SPACE");
		mText.DrawString(buf, -220, -50, 18, 18);
	}
	//�S�[��
	else if (CGoal::mTouchGoal == true) {
		glColor4f(0.1f, 0.3f, 0.8f, 1.0f);
		sprintf(buf, "GOAL");
		mText.DrawString(buf, -120, 0, 35, 35);
	}
	//�Q�[���I�[�o�[
	else if (mPlayerHp == 0) {
		glColor4f(0.5f, 0.3f, 0.3f, 1.0f);
		sprintf(buf, "FAILED");
		mText.DrawString(buf, -150, 0, 35, 35);
		glColor4f(0.5f, 0.6f, 0.8f, 1.0f);
		sprintf(buf, "RESTART TO R");
		mText.DrawString(buf, -220, -50, 20, 20);
		sprintf(buf, "CONTINUE TO T");
		mText.DrawString(buf, -260, -100, 20, 20);
	}
	//�Ə�(��)
	else if (CGoal::mTouchGoal != true) {
		//������̐ݒ�
		sprintf(buf, "[+]");
		//������̕`��
		mText.DrawString(buf, -30, 20, 15, 15);
	}

	//2D�`��I��
	CUtil::End2D();
}

//�Փˏ���
void CPlayer::TaskCollision(){
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	mCollider.ChangePriority();
	mSearchLine.ChangePriority();
	//�Փˏ��� ���s
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mSearchLine, COLLISIONRANGE);
}