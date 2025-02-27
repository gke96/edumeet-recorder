/* Copyright (C) 2020
 *
 * Authors: TT Wojciech Kapsa
 */

#ifndef RECORDER_SERVICE_HTML_RECORDER_H
#define RECORDER_SERVICE_HTML_RECORDER_H

#include "IRecorder.h"
#include <nlohmann/json.hpp>

namespace rec {
enum class EncoderType
{
    H264,
    VP8
};
NLOHMANN_JSON_SERIALIZE_ENUM(EncoderType, { { EncoderType::H264, "h264" }, { EncoderType::VP8, "vp8" } })

enum class EncoderMode
{
    RECORD,
    STREAM,
    BOTH
};
NLOHMANN_JSON_SERIALIZE_ENUM(EncoderMode, { { EncoderMode::RECORD, "record" }, { EncoderMode::STREAM, "stream" }, { EncoderMode::BOTH, "both" } })

class CHtmlEncoder : public IRecorder
{
public:
    struct Params
    {
        int bitrate = 0;
        std::string uri {};
        EncoderType encoder { EncoderType::H264 };
        EncoderMode mode { EncoderMode::RECORD };
        std::string stream_uri;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Params, bitrate, uri, encoder, mode, stream_uri)
    };

    explicit CHtmlEncoder(std::filesystem::path workdir, Params params);
    bool start() override;
    bool stop() override;
    ~CHtmlEncoder() override = default;

private:
    static std::string createCmd(const Params&, const std::string& location);
    Params m_params;
};

} // namespace rec

#endif // RECORDER_SERVICE_HTML_RECORDER_H
