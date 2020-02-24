#include "ClawController.h"

ClawController::ClawController(t_actuatorConfig actuatorConfig, 
                       Motor &motor, Encoder &encoder,  
                       DigitalIn &limSwitchMax, AnalogIn &forceSensor, Servo &tooltipServo,
                       float tooltipExtendedAngle_Degrees, float tooltipRetractedAngle_Degrees) : 
        ActuatorController(actuatorConfig, motor, encoder, NULL_DIGITAL_IN, limSwitchMax), r_forceSensor(forceSensor), r_tooltipServo(tooltipServo),
        m_tooltipExtendedAngle_Degrees(tooltipExtendedAngle_Degrees), m_tooltipRetractedAngle_Degrees(tooltipRetractedAngle_Degrees) {};


mbed_error_status_t ClawController::setGapVelocity_CmPerSec(float cmPerSec) {
    float shaftVelocity_DegreesPerSec = 2.0 * cmPerSec + 0.0 * getGapDistance_Cm(); // TODO find mapping function (velocity dependent on position)
    return setVelocity_DegreesPerSec(shaftVelocity_DegreesPerSec);
}

mbed_error_status_t ClawController::setGapDistance_Cm(float cm) {
    float shaftPosition_Degrees = 2.0 * cm; // TODO find mapping function
    return setAngle_Degrees(shaftPosition_Degrees);
}

mbed_error_status_t ClawController::setMotionData(float motionData) {
    switch(getControlMode()) {
        case t_actuatorControlMode::motorPower:
            return setMotorPower_Percentage(motionData);
        case t_actuatorControlMode::velocity:
            return setGapVelocity_CmPerSec(motionData);
        case t_actuatorControlMode::position:
            return setGapDistance_Cm(motionData);
        default: 
            return MBED_ERROR_INVALID_ARGUMENT;
    }
}

mbed_error_status_t ClawController::extendToolTip() {
    mbed_error_status_t err_status = r_tooltipServo.set_position(m_tooltipExtendedAngle_Degrees) ? MBED_SUCCESS : MBED_ERROR_INVALID_OPERATION;
    return err_status;
}

mbed_error_status_t ClawController::retractToolTip() {
    mbed_error_status_t err_status = r_tooltipServo.set_position(m_tooltipRetractedAngle_Degrees) ? MBED_SUCCESS : MBED_ERROR_INVALID_OPERATION;
    return err_status;
}


float ClawController::getGapVelocity_CmPerSec() {
    return getVelocity_DegreesPerSec() / 2.0 + 0.0 * getAngle_Degrees(); // TODO find mapping function (velocity dependent on position)
}
float ClawController::getGapDistance_Cm() {
    return getAngle_Degrees() / 2.0; // TODO find mapping function
}

float ClawController::getGripForce_Newtons() {
    return 0.0; // TODO
}

mbed_error_status_t ClawController::runPositionCalibration() {
    return MBED_SUCCESS; // TODO
}

float ClawController::convertShaftPositionDegreesToGapCm(float shaftPosition_Degrees) {
    return (6.363885761e-7)*(shaftPosition_Degrees*shaftPosition_Degrees) - (8.793434733e-3)*shaftPosition_Degrees + 15.80749897;
}

float ClawController::convertGapCmToShaftPositionDegrees(float gap_cm) {
    return (1.573564198)*(gap_cm*gap_cm)- (158.4968661)*gap_cm + 2119.701587;
    // return (8.282382533e-3)*(gap_cm*gap_cm*gap_cm*gap_cm) - (2.986760459e-1)*(gap_cm*gap_cm*gap_cm) + (5.007842722)*(gap_cm*gap_cm) - (171.560244)*gap_cm + 2127.848743; // High precision 
}
