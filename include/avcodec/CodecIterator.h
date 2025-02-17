#pragma once

#include <cstddef>
#include <iterator>
#include <ranges>

#include "Codec.h"

namespace ffmpeg {

class CodecIterator {
public:
    using difference_type = std::ptrdiff_t;
    using value_type = const Codec;

    CodecIterator() noexcept;

    const Codec& operator*() const noexcept;
    const Codec* operator->() const noexcept;

    CodecIterator& operator++() noexcept;
    CodecIterator operator++(int) noexcept;

    bool operator==(const CodecIterator& other) const noexcept;

    static CodecIterator begin() noexcept;
    static CodecIterator end() noexcept;

private:
    void* m_state;
    Codec m_currentCodec;

    void next() noexcept;
};

static_assert(std::input_iterator<CodecIterator>);
static_assert(std::ranges::range<CodecIterator>);

}// namespace ffmpeg
