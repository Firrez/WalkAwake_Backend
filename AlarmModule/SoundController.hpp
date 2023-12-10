#pragma once

namespace AlarmModule {

    class SoundController {
    public:
        SoundController();
        void Play();
        int Stop();
        virtual ~SoundController();

    private:
        void Replay();
    };

} // AlarmModule