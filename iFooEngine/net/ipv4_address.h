#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include "common.h"

namespace foo::net
{
	class FOODLLTYPE ipv4_address
	{
		using bytes_t = std::uint8_t[4];

	public:

		constexpr ipv4_address()
			: bytes_{ 0, 0, 0, 0 }
		{}

		explicit constexpr ipv4_address(std::uint32_t integer)
			: bytes_{
			static_cast<std::uint8_t>(integer >> 24),
			static_cast<std::uint8_t>(integer >> 16),
			static_cast<std::uint8_t>(integer >> 8),
			static_cast<std::uint8_t>(integer) }
		{}

		explicit constexpr ipv4_address(const std::uint8_t(&bytes)[4])
			: bytes_{ bytes[0], bytes[1], bytes[2], bytes[3] }
		{}

		explicit constexpr ipv4_address(
			std::uint8_t b0,
			std::uint8_t b1,
			std::uint8_t b2,
			std::uint8_t b3)
			: bytes_{ b0, b1, b2, b3 }
		{}

		constexpr const bytes_t& bytes() const { return bytes_; }

		constexpr std::uint32_t to_integer() const
		{
			return
				std::uint32_t(bytes_[0]) << 24 |
				std::uint32_t(bytes_[1]) << 16 |
				std::uint32_t(bytes_[2]) << 8 |
				std::uint32_t(bytes_[3]);
		}

		static constexpr ipv4_address loopback()
		{
			return ipv4_address(127, 0, 0, 1);
		}

		constexpr bool is_loopback() const
		{
			return bytes_[0] == 127;
		}

		constexpr bool is_private_network() const
		{
			return bytes_[0] == 10 ||
				(bytes_[0] == 172 && (bytes_[1] & 0xF0) == 0x10) ||
				(bytes_[0] == 192 && bytes_[2] == 168);
		}

		constexpr bool operator==(ipv4_address other) const
		{
			return
				bytes_[0] == other.bytes_[0] &&
				bytes_[1] == other.bytes_[1] &&
				bytes_[2] == other.bytes_[2] &&
				bytes_[3] == other.bytes_[3];
		}

		constexpr bool operator!=(ipv4_address other) const
		{
			return !(*this == other);
		}

		constexpr bool operator<(ipv4_address other) const
		{
			return to_integer() < other.to_integer();
		}

		constexpr bool operator>(ipv4_address other) const
		{
			return other < *this;
		}

		constexpr bool operator<=(ipv4_address other) const
		{
			return !(other < *this);
		}

		constexpr bool operator>=(ipv4_address other) const
		{
			return !(*this < other);
		}

		static std::optional<ipv4_address> from_string(std::string_view string) noexcept;

		std::string to_string() const;
	private:
		alignas(std::uint32_t) std::uint8_t bytes_[4];
	};
}