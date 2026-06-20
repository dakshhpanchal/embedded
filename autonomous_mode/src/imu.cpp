#include "imu.h"

static Adafruit_BNO08x  _bno(-1);
static sh2_SensorValue_t _sv;
static bool  _ok = false;
static float _yaw, _pitch, _roll, _qx, _qy, _qz, _qw;

void imuSetup() {
    Wire1.begin();
    Wire1.setClock(400000);
    pinMode(BNO08X_INT, INPUT_PULLUP);
    if (!_bno.begin_I2C(BNO08x_I2CADDR_DEFAULT, &Wire1)) {
        Serial.println("[IMU] NOT FOUND");
        return;
    }
    _bno.enableReport(SH2_ROTATION_VECTOR, 50000);
    _ok = true;
    Serial.println("[IMU] OK");
}

bool imuUpdate() {
    if (!_ok) return false;
    if (!_bno.getSensorEvent(&_sv)) return false;
    if (_sv.sensorId != SH2_ROTATION_VECTOR) return false;

    _qw = _sv.un.rotationVector.real;
    _qx = _sv.un.rotationVector.i;
    _qy = _sv.un.rotationVector.j;
    _qz = _sv.un.rotationVector.k;

    float sqw = sq(_qw), sqx = sq(_qx), sqy = sq(_qy), sqz = sq(_qz);
    _yaw   = atan2(2.0f*(_qx*_qy + _qz*_qw), (sqx - sqy - sqz + sqw)) * RAD_TO_DEG;
    _pitch = asin(-2.0f*(_qx*_qz - _qy*_qw) / (sqx+sqy+sqz+sqw))      * RAD_TO_DEG;
    _roll  = atan2(2.0f*(_qy*_qz + _qx*_qw), (-sqx - sqy + sqz + sqw)) * RAD_TO_DEG;
    return true;
}

float imuYaw()   { return _yaw;   }
float imuPitch() { return _pitch; }
float imuRoll()  { return _roll;  }
float imuQx()    { return _qx;    }
float imuQy()    { return _qy;    }
float imuQz()    { return _qz;    }
float imuQw()    { return _qw;    }