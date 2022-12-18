#pragma once
#include "pch.h"

class BALL {
private:
        //���W
        double x, y;

        //�O���t�B�b�N�n���h��
        int gh;

        //�ꎞ�t���O
        bool toggle;

        //sin�g�Ɏg���p�x�̑�����
        int raise;

        //�p�x
        double angle;

private:
        void Move(double px, double py);
        void Draw();
public:
        BALL();
        void All(double px, double py);
        double GetPosition();

};



