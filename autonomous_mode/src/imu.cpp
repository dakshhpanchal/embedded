#include "imu.h"

static Adafruit_BNO08x  _bno(-1);
static sh2_SensorValue_t _sv;
static bool  _ok = false;
static float _yaw, _pitch, _roll;
static float _qx, _qy, _qz, _qw;
static float _gx, _gy, _gz;
static float _ax, _ay, _az;

void imuSetup() {
    Wire1.begin();
    Wire1.setClock(400000);

    // BNO08X_RESET was declared in config.h but never actually driven.
    // Force it into a known state before talking to the sensor: hold
    // reset LOW briefly, then release (HIGH) so the chip always starts
    // from the same clean state instead of whatever it powered up in.
    pinMode(BNO08X_RESET, OUTPUT);
    digitalWrite(BNO08X_RESET, LOW);
    delay(10);
    digitalWrite(BNO08X_RESET, HIGH);
    delay(10);

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

    switch (_sv.sensorId) {
        case SH2_ROTATION_VECTOR:
            _qw = _sv.un.rotationVector.real;
            _qx = _sv.un.rotationVector.i;
            _qy = _sv.un.rotationVector.j;
            _qz = _sv.un.rotationVector.k;

            float sqw = sq(_qw), sqx = sq(_qx), sqy = sq(_qy), sqz = sq(_qz);
            _yaw   = atan2(2.0f*(_qx*_qy + _qz*_qw), (sqx - sqy - sqz + sqw)) * RAD_TO_DEG;
            _pitch = asin(-2.0f*(_qx*_qz - _qy*_qw) / (sqx+sqy+sqz+sqw))      * RAD_TO_DEG;
            _roll  = atan2(2.0f*(_qy*_qz + _qx*_qw), (-sqx - sqy + sqz + sqw)) * RAD_TO_DEG;
            return true;

        case SH2_GYRO_INTEGRATED_RV:
            _gx = _sv.un.gyroscope.x;
            _gy = _sv.un.gyroscope.y;
            _gz = _sv.un.gyroscope.z;
            return true;

        case SH2_LINEAR_ACCELERATION:
            _ax = _sv.un.accelerometer.x;
            _ay = _sv.un.accelerometer.y;
            _az = _sv.un.accelerometer.z;
            return true;

        default:
            return false;
    }
}

float imuYaw()   { return _yaw;   }
float imuPitch() { return _pitch; }
float imuRoll()  { return _roll;  }
float imuQx()    { return _qx;    }
float imuQy()    { return _qy;    }
float imuQz()    { return _qz;    }
float imuQw()    { return _qw;    }
float imuGx()    { return _gx;    }
float imuGy()    { return _gy;    }
float imuGz()    { return _gz;    }
float imuAx()    { return _ax;    }
float imuAy()    { return _ay;    }
float imuAz()    { return _az;    }