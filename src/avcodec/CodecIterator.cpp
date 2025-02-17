#include "CodecIterator.h"
#include "Codec.h"

extern "C" {
#include <libavcodec/codec.h>
}

namespace ffmpeg {

CodecIterator::CodecIterator() noexcept: m_state{nullptr}, m_currentCodec(nullptr) {
}

const Codec& CodecIterator::operator*() const noexcept {
    return m_currentCodec;
}

const Codec* CodecIterator::operator->() const noexcept {
    return &m_currentCodec;
}

CodecIterator& CodecIterator::operator++() noexcept {
    next();
    return *this;
}

CodecIterator CodecIterator::operator++(int) noexcept {
    CodecIterator copy = *this;
    next();
    return copy;
}

bool CodecIterator::operator==(const CodecIterator& other) const noexcept {
    return m_state == other.m_state;
}

CodecIterator CodecIterator::begin() noexcept {
    CodecIterator res;
    res.next();
    return res;
}

CodecIterator CodecIterator::end() noexcept {
    return {};
}

void CodecIterator::next() noexcept {
    m_currentCodec = Codec(av_codec_iterate(&m_state));
}

}// namespace ffmpeg
