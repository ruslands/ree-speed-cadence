#include "fusion.h"
#include "nrf_log.h"

// Simple dummy step counter from accel
static int16_t last_ax = 0;
static int crank_rpm = 0;

void fusion_init(void)
{
    last_ax = 0;
    crank_rpm = 0;
}

void fusion_step(void)
{
    // Simulate cadence detection (placeholder)
    static uint32_t count = 0;
    count++;
    if (count % 1000 == 0)
    {
        crank_rpm = (crank_rpm + 5) % 120; // dummy simulated RPM
        NRF_LOG_INFO("Estimated Cadence: %d RPM", crank_rpm);
    }
}
