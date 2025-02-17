#pragma once

#include <cstdint>
#include <span>
#include <string_view>

extern "C" {
#include <libavcodec/codec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/log.h>
#include <libavutil/pixfmt.h>
#include <libavutil/rational.h>
#include <libavutil/samplefmt.h>
}

namespace ffmpeg {

class Codec {
public:
    explicit Codec(const AVCodec* codec) noexcept;

    std::string_view getName() const noexcept;
    std::string_view getLongName() const noexcept;
    std::string_view getWrapperName() const noexcept;

    AVCodecID getID() const noexcept;
    int getCapabilites() const noexcept;
    uint8_t getMaxLowres() const noexcept;
    const AVClass* getClass() const noexcept;

    std::span<const AVRational> getFrameRates() const noexcept;
    std::span<const AVPixelFormat> getPixelFormats() const noexcept;
    std::span<const int> getSampleRates() const noexcept;
    std::span<const AVSampleFormat> getSampleFormats() const noexcept;
    std::span<const AVProfile> getProfiles() const noexcept;
    std::span<const AVChannelLayout> getChannelLayouts() const noexcept;

    bool isDecoder() const noexcept;
    bool isEncoder() const noexcept;

private:
    const AVCodec* m_codec;
};

}// namespace ffmpeg
