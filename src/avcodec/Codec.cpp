#include "Codec.h"

#include <cstddef>
#include <functional>
#include <string_view>

extern "C" {
#include <libavcodec/codec.h>
#include <libavcodec/codec_id.h>
#include <libavcodec/defs.h>
#include <libavutil/channel_layout.h>
#include <libavutil/pixfmt.h>
#include <libavutil/rational.h>
#include <libavutil/samplefmt.h>
}

namespace {

std::string_view toStringView(const char* str) {
    if (str == nullptr) return "";
    return str;
}

template <typename T, typename Pred>
    requires std::is_nothrow_invocable_r_v<bool, Pred, const T&>
std::span<const T> toSpan(const T* arr, const Pred& isTerminator) noexcept {
    if (arr == nullptr) return {};
    size_t sz = 0;
    while (!std::invoke_r<bool>(isTerminator, arr[sz])) {
        ++sz;
    }
    return {arr, sz};
}

}// namespace

namespace ffmpeg {

Codec::Codec(const AVCodec* codec) noexcept: m_codec(codec) {
}

std::string_view Codec::getName() const noexcept {
    return toStringView(m_codec->name);
}

std::string_view Codec::getLongName() const noexcept {
    return toStringView(m_codec->long_name);
}

std::string_view Codec::getWrapperName() const noexcept {
    return toStringView(m_codec->wrapper_name);
}

AVCodecID Codec::getID() const noexcept {
    return m_codec->id;
}

int Codec::getCapabilites() const noexcept {
    return m_codec->capabilities;
}

uint8_t Codec::getMaxLowres() const noexcept {
    return m_codec->max_lowres;
}

const AVClass* Codec::getClass() const noexcept {
    return m_codec->priv_class;
}

std::span<const AVRational> Codec::getFrameRates() const noexcept {
    return toSpan(m_codec->supported_framerates,
                  [](AVRational rate) noexcept { return rate.num == 0 && rate.den == 0; });
}

std::span<const AVPixelFormat> Codec::getPixelFormats() const noexcept {
    return toSpan(m_codec->pix_fmts, [](AVPixelFormat pixFmt) noexcept { return pixFmt == -1; });
}

std::span<const int> Codec::getSampleRates() const noexcept {
    return toSpan(m_codec->supported_samplerates, [](int sampleRate) noexcept { return sampleRate == 0; });
}

std::span<const AVSampleFormat> Codec::getSampleFormats() const noexcept {
    return toSpan(m_codec->sample_fmts, [](AVSampleFormat sampleFmt) noexcept { return sampleFmt == 0; });
}

std::span<const AVProfile> Codec::getProfiles() const noexcept {
    return toSpan(m_codec->profiles,
                  [](const AVProfile& profile) noexcept { return profile.profile == AV_PROFILE_UNKNOWN; });
}

std::span<const AVChannelLayout> Codec::getChannelLayouts() const noexcept {
    return toSpan(m_codec->ch_layouts, [](const AVChannelLayout& layout) noexcept {
        // zeroed layout
        return layout.order == 0 && layout.nb_channels == 0 && layout.u.mask == 0 && layout.opaque == nullptr;
    });
}

}// namespace ffmpeg
