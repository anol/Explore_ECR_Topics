/*
 * qei_sensor.h
 *
 *  Created on: 23. mars 2015
 *      Author: Anders
 */

#ifndef QEI_SENSOR_H_
#define QEI_SENSOR_H_

#include "inc/hw_memmap.h"
#include "driverlib/qei.h"

namespace Aeo_2 {

class QEI_sensor {
public:
	enum configuration {
		DefaultConfiguration = (QEI_CONFIG_CAPTURE_A | QEI_CONFIG_NO_RESET
				| QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP),
		SwapPins = (QEI_CONFIG_CAPTURE_A | QEI_CONFIG_NO_RESET
				| QEI_CONFIG_QUADRATURE | QEI_CONFIG_SWAP)
	};
	enum device_id {
		QEI0, QEI1
	};

public:
	typedef void (*OnIndex)();

public:
	explicit QEI_sensor(device_id nDevice, configuration nConfig = DefaultConfiguration);

public:
	void initialize();
	int32_t get_position() const;
	bool GetIndex();
	void Set( int32_t nValue ) const;
	void zero() const;
	void diag();

private:
	device_id m_nDevice;
	uint32_t m_ui32Base;
	configuration m_nConfig;
};

} /* namespace Aeo_2 */

#endif /* QEI_SENSOR_H_ */
