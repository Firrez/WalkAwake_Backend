#pragma once

namespace AlarmModule {

    class SoundController {
    public:
        SoundController();
        int Play();
        int Stop();
        virtual ~SoundController();

    private:
        void Replay();
    };

} // AlarmModule