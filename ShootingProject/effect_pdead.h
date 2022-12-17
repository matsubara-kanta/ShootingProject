#pragma once
#include "pch.h"

class EFFECT_PDEAD {
private:
        //���W
        double x, y;

        //�摜�̃T�C�Y
        int width[3];
        int height[3];

        //�O���t�B�b�N�n���h��
        int gh[3];

        //�g�嗦
        double rate;

        //�����x
        int alpha;

        //�p�[�e�B�N���G�t�F�N�g�\����
        PEFFECT_EXPAND expand[EFFECT_PDEADNUM];

        //��]������摜�p�̊p�x
        double rota;

        //�J�E���g
        int count;

        //���s�����ǂ����̃t���O
        bool flag;

private:
        void Move();
        void Draw();
public:
        EFFECT_PDEAD();
        void SetFlag(double x, double y);
        bool GetFlag();
        void All();
};
