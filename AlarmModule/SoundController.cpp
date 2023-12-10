#include "SoundController.hpp"
#include <ao/ao.h>
#include <mpg123.h>

#define BITS 8
#define PATH "../music.mp3"

using namespace AlarmModule;

bool m_bPlay;

SoundController::SoundController() = default;

void SoundController::Play() {
    m_bPlay = true;

    mpg123_handle *m_mpgHandle;
    unsigned char *m_szBuffer;
    size_t m_sBuffer_size;
    size_t m_sDone;
    int m_iErr;

    int m_iDriver;
    ao_device *m_aoDev;

    ao_sample_format m_aosFormat;
    int m_iChannels, m_iEncoding;
    long m_lRate;

    ao_initialize();
    m_iDriver = ao_default_driver_id();
    mpg123_init();
    m_mpgHandle = mpg123_new(nullptr, &m_iErr);
    m_sBuffer_size = mpg123_outblock(m_mpgHandle);
    m_szBuffer = (unsigned char*) malloc(m_sBuffer_size * sizeof(unsigned char));

    mpg123_open(m_mpgHandle, PATH);
    mpg123_getformat(m_mpgHandle, &m_lRate, &m_iChannels, &m_iEncoding);

    m_aosFormat.bits = mpg123_encsize(m_iEncoding) * BITS;
    m_aosFormat.rate = m_lRate;
    m_aosFormat.channels = m_iChannels;
    m_aosFormat.byte_format = AO_FMT_NATIVE;
    m_aosFormat.matrix = nullptr;
    m_aoDev = ao_open_live(m_iDriver, &m_aosFormat, nullptr);

    while (mpg123_read(m_mpgHandle, m_szBuffer, m_sBuffer_size, &m_sDone) == MPG123_OK && m_bPlay) {
        ao_play(m_aoDev, (char*)m_szBuffer, m_sDone);

    }

    free(m_szBuffer);
    ao_close(m_aoDev);
    mpg123_close(m_mpgHandle);
    mpg123_delete(m_mpgHandle);
    mpg123_exit();
    ao_shutdown();

    Replay();
}

int SoundController::Stop() {
    m_bPlay = false;
    return EXIT_SUCCESS;
}

void SoundController::Replay() {
    if (m_bPlay)
        Play();
}

SoundController::~SoundController() = default;
