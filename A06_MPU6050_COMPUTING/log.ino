#include "MPU6050.h"
#include "I2Cdev.h"
#include "quard_copter.h"

#if defined(LOG_MPU6050_INFO)
void printMpu6050Status() {
	Serial.println("::::: checking MPU6050 sensor :::::");
	Serial.print(" > Sleep Mode              : ");
	Serial.println(sensMpu.getSleepEnabled() ? "Enabled" : "Disabled");
	Serial.print(" > Accelerometer Range     : ");
	switch(sensMpu.getFullScaleAccelRange()) {
		case 0:	Serial.print("+/- 2g >> "); break;
		case 1:	Serial.print("+/- 4g >> "); break;
		case 2:	Serial.print("+/- 8g >> "); break;
		case 3:	Serial.print("+/- 16g >> "); break;
	}
	Serial.print(sensMpu.getAccelRangePerDigit(), 7);
	Serial.println(" rangePerDigit");
	Serial.print(" > Gyroscope Scale         : ");
	switch(sensMpu.getFullScaleGyroRange()) {
		case 0:	Serial.print("+/- 250 degrees/sec >> "); break;
		case 1:	Serial.print("+/- 500 degrees/sec >> "); break;
		case 2:	Serial.print("+/- 1000 degrees/sec >> "); break;
		case 3:	Serial.print("+/- 2000 degrees/sec >> "); break;
	}
	Serial.print(sensMpu.getGyroRangePerDigit(), 7);
	Serial.println(" dpsPerDigit");
	Serial.print(" > DLPF Mode               : ");
	switch(sensMpu.getDLPFMode()) {
    case 0: Serial.println("260Hz DELAY[Accel:0ms, Gyro:0.98ms]"); break;
    case 1: Serial.println("184Hz DELAY[Accel:2ms, Gyro:1.9ms]"); break;
    case 2: Serial.println("94Hz DELAY[Accel:3ms, Gyro:2.8ms]"); break;
    case 3: Serial.println("44Hz DELAY[Accel:4.9ms, Gyro:4.8ms]"); break;
    case 4: Serial.println("21Hz DELAY[Accel:8.5ms, Gyro:8.3ms]"); break;
    case 5: Serial.println("10Hz DELAY[Accel:13.8ms, Gyro:13.4ms]"); break;
    case 6: Serial.println("5Hz DELAY[Accel:19ms, Gyro:18.6ms]"); break;
	}

	Serial.print(" > Accelerometer DHPF Mode : ");
	switch(sensMpu.getDHPFMode()) {
    case 0: Serial.println("Reset / None"); break;
    case 1: Serial.println("On / 5Hz cut-off"); break;
    case 2: Serial.println("On / 2.5Hz cut-off"); break;
    case 3: Serial.println("On / 1.25Hz cut-off"); break;
    case 4: Serial.println("On / 0.63Hz cut-off"); break;
    case 5: Serial.println("Hold / None"); break;
	}

	Serial.print(" > Accelerometer offsets   [x:");
	Serial.print(sensMpu.getXAccelOffset());
	Serial.print(", y:");
	Serial.print(sensMpu.getYAccelOffset());
	Serial.print(", z:");
	Serial.print(sensMpu.getZAccelOffset());
	Serial.println("]");

	Serial.print(" > Gyroscope offsets       [x:");
	Serial.print(sensMpu.getXGyroOffset());
	Serial.print(", y:");
	Serial.print(sensMpu.getYGyroOffset());
	Serial.print(", z:");
	Serial.print(sensMpu.getZGyroOffset());
	Serial.println("]");
}
#endif

#if defined(LOG_MPU6050_DATA)
void printMpu6050Data() {
	bool isOnAccel = false, isOnGyro = false;
	#if defined(LOG_MPU6050_DATA_ACCELOMETER_LAW)
		if (!isOnAccel) {
			Serial.print("ACEL "); isOnAccel = true;
		}
		Serial.print("RAW[x:");
		Serial.print(mpu6050raw[0]);
		Serial.print(", y:");
		Serial.print(mpu6050raw[1]);
		Serial.print(", z:");
		Serial.print(mpu6050raw[2]);
		Serial.print("] ");
	#endif
	#if defined(LOG_MPU6050_DATA_ACCELOMETER_BASE)
		if (!isOnAccel) {
			Serial.print("ACEL "); isOnAccel = true;
		}
		Serial.print("BASE[x:");
		Serial.print(acelBase.x);
		Serial.print(", y:");
		Serial.print(acelBase.y);
		Serial.print(", z:");
		Serial.print(acelBase.z);
		Serial.print("] ");
	#endif
	#if defined(LOG_MPU6050_DATA_ACCELOMETER_AXIS)
		if (!isOnAccel) {
			Serial.print("ACEL "); isOnAccel = true;
		}
		Serial.print("AXIS[x:");
		Serial.print(acelAxis.x);
		Serial.print(", y:");
		Serial.print(acelAxis.y);
		Serial.print(", z:");
		Serial.print(acelAxis.z);
		Serial.print("] ");
	#endif
	#if defined(LOG_MPU6050_DATA_ACCELOMETER_ANGLE)
		if (!isOnAccel) {
			Serial.print("ACEL "); isOnAccel = true;
		}
		Serial.print("ANGLE[x:");
		Serial.print(acelAngl.x);
		Serial.print(", y:");
		Serial.print(acelAngl.y);
		Serial.print(", z:");
		Serial.print(acelAngl.z);
		Serial.print("] ");
	#endif

	#if defined(LOG_MPU6050_DATA_GYRO_LAW)
		if (!isOnGyro) {
			Serial.print("GYRO "); isOnGyro = true;
		}
		Serial.print("RAW[x:");
		Serial.print(mpu6050raw[3]);
		Serial.print(", y:");
		Serial.print(mpu6050raw[4]);
		Serial.print(", z:");
		Serial.print(mpu6050raw[5]);
		Serial.print("] ");
	#endif
	#if defined(LOG_MPU6050_DATA_GYRO_BASE)
		if (!isOnGyro) {
			Serial.print("GYRO "); isOnGyro = true;
		}
		Serial.print("BASE[x:");
		Serial.print(gyroBase.x);
		Serial.print(", y:");
		Serial.print(gyroBase.y);
		Serial.print(", z:");
		Serial.print(gyroBase.z);
		Serial.print("] ");
	#endif
	#if defined(LOG_MPU6050_DATA_GYRO_AXIS)
		if (!isOnGyro) {
			Serial.print("GYRO "); isOnGyro = true;
		}
		Serial.print("AXIS[x:");
		Serial.print(gyroAxis.x);
		Serial.print(", y:");
		Serial.print(gyroAxis.y);
		Serial.print(", z:");
		Serial.print(gyroAxis.z);
		Serial.print("] ");
	#endif
	#if defined(LOG_MPU6050_DATA_GYRO_ANGLE)
		if (!isOnGyro) {
			Serial.print("GYRO "); isOnGyro = true;
		}
		Serial.print("ANGLE[x:");
		Serial.print(gyroAngl.x);
		Serial.print(", y:");
		Serial.print(gyroAngl.y);
		Serial.print(", z:");
		Serial.print(gyroAngl.z);
		Serial.print("] ");
	#endif

	#if defined(LOG_MPU6050_DRON_ANGLE)
		Serial.print("GYRO ANGLE[x:");
		Serial.print(angle.x);
		Serial.print(", y:");
		Serial.print(angle.y);
		Serial.print(", z:");
		Serial.print(angle.z);
		Serial.print("] ");
	#endif
	Serial.println("");
}
#endif

#if defined(LOG_MOTOR_INFO)
void printMotorPower() {
	Serial.print("MOTOR[1:"); Serial.print(motor_power.m1);
	Serial.print(", 2:"); Serial.print(motor_power.m2);
	Serial.print(", 3:"); Serial.print(motor_power.m3);
	Serial.print(", 4:"); Serial.print(motor_power.m4);
	Serial.println("]");
}
#endif

#if defined(LOG_MONITORING)
void printMonitoring() {
	#if defined(LOG_MONITORING_LAW)
		Serial.print(mpu6050raw[0]); Serial.print(",");
		Serial.print(mpu6050raw[1]); Serial.print(",");
		Serial.print(mpu6050raw[2]); Serial.print(",");
		Serial.print(mpu6050raw[3]); Serial.print(",");
		Serial.print(mpu6050raw[4]); Serial.print(",");
		Serial.print(mpu6050raw[5]); Serial.print(",");
		Serial.println();
	#endif
	#if defined(LOG_MONITORING_AXIS)
		Serial.print(acelAxis.x); Serial.print(",");
		Serial.print(acelAxis.y); Serial.print(",");
		Serial.print(acelAxis.z); Serial.print(",");
		Serial.print(gyroAxis.x); Serial.print(",");
		Serial.print(gyroAxis.y); Serial.print(",");
		Serial.print(gyroAxis.z); Serial.print(",");
		Serial.println();
	#endif
	#if defined(LOG_MONITORING_ANGLE)
		Serial.print(acelAngl.x); Serial.print(",");
		Serial.print(acelAngl.y); Serial.print(",");
		Serial.print(acelAngl.z); Serial.print(",");
		Serial.print(gyroAngl.x); Serial.print(",");
		Serial.print(gyroAngl.y); Serial.print(",");
		Serial.print(gyroAngl.z); Serial.print(",");
		Serial.println();
	#endif
	#if defined(LOG_MONITORING_DRON_ANGLE)
		Serial.print(gyroAngl.x); Serial.print(",");
		Serial.print(gyroAngl.y); Serial.print(",");
		Serial.print(gyroAngl.z); Serial.print(",");
		Serial.print(angle.x); Serial.print(",");
		Serial.print(angle.y); Serial.print(",");
		Serial.print(angle.z); Serial.print(",");
		Serial.println();
	#endif

	#if defined(LOG_MONITORING_DRON)
		Serial.print(F("DEL:"));              //Delta T
		Serial.print(delta, DEC);
		Serial.print(F("#ACC:"));              //Accelerometer angle
		Serial.print(acelAngl.x, 2);
		Serial.print(F(","));
		Serial.print(acelAngl.y, 2);
		Serial.print(F(","));
		Serial.print(acelAngl.z, 2);
		Serial.print(F("#GYR:"));
		Serial.print(gyroAngl.x, 2);        //Gyroscope angle
		Serial.print(F(","));
		Serial.print(gyroAngl.y, 2);
		Serial.print(F(","));
		Serial.print(gyroAngl.z, 2);
		Serial.print(F("#FIL:"));             //Filtered angle
		Serial.print(angle.x, 2);
		Serial.print(F(","));
		Serial.print(angle.y, 2);
		Serial.print(F(","));
		Serial.print(angle.z, 2);
		Serial.println(F(""));
	#endif
}
#endif