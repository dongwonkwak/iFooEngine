#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

#include "common.h"


namespace foo::net
{
	class ipv4_address;

	class FOODLLTYPE ipv6_address
	{
		using bytes_t = std::uint8_t[16];

	public:

		constexpr ipv6_address();

		explicit constexpr ipv6_address(
			std::uint64_t subnetPrefix,
			std::uint64_t interfaceIdentifier);

		constexpr ipv6_address(
			std::uint16_t part0,
			std::uint16_t part1,
			std::uint16_t part2,
			std::uint16_t part3,
			std::uint16_t part4,
			std::uint16_t part5,
			std::uint16_t part6,
			std::uint16_t part7);

		explicit constexpr ipv6_address(
			const std::uint16_t(&parts)[8]);

		explicit constexpr ipv6_address(
			const std::uint8_t(&bytes)[16]);

		constexpr const bytes_t& bytes() const { return bytes_; }

		constexpr std::uint64_t subnet_prefix() const;

		constexpr std::uint64_t interface_identifier() const;

		static constexpr ipv6_address unspecified();

		static constexpr ipv6_address loopback();

		static std::optional<ipv6_address> from_string(std::string_view string) noexcept;

		std::string to_string() const;

		constexpr bool operator==(const ipv6_address& other) const;
		constexpr bool operator!=(const ipv6_address& other) const;
		constexpr bool operator<(const ipv6_address& other) const;
		constexpr bool operator>(const ipv6_address& other) const;
		constexpr bool operator<=(const ipv6_address& other) const;
		constexpr bool operator>=(const ipv6_address& other) const;

	private:

		alignas(std::uint64_t) std::uint8_t bytes_[16];

	};

	constexpr ipv6_address::ipv6_address()
		: bytes_{
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0 }
	{}

	constexpr ipv6_address::ipv6_address(
		std::uint64_t subnetPrefix,
		std::uint64_t interfaceIdentifier)
		: bytes_{
			static_cast<std::uint8_t>(subnetPrefix >> 56),
			static_cast<std::uint8_t>(subnetPrefix >> 48),
			static_cast<std::uint8_t>(subnetPrefix >> 40),
			static_cast<std::uint8_t>(subnetPrefix >> 32),
			static_cast<std::uint8_t>(subnetPrefix >> 24),
			static_cast<std::uint8_t>(subnetPrefix >> 16),
			static_cast<std::uint8_t>(subnetPrefix >> 8),
			static_cast<std::uint8_t>(subnetPrefix),
			static_cast<std::uint8_t>(interfaceIdentifier >> 56),
			static_cast<std::uint8_t>(interfaceIdentifier >> 48),
			static_cast<std::uint8_t>(interfaceIdentifier >> 40),
			static_cast<std::uint8_t>(interfaceIdentifier >> 32),
			static_cast<std::uint8_t>(interfaceIdentifier >> 24),
			static_cast<std::uint8_t>(interfaceIdentifier >> 16),
			static_cast<std::uint8_t>(interfaceIdentifier >> 8),
			static_cast<std::uint8_t>(interfaceIdentifier) }
	{}

	constexpr ipv6_address::ipv6_address(
		std::uint16_t part0,
		std::uint16_t part1,
		std::uint16_t part2,
		std::uint16_t part3,
		std::uint16_t part4,
		std::uint16_t part5,
		std::uint16_t part6,
		std::uint16_t part7)
		: bytes_{
			static_cast<std::uint8_t>(part0 >> 8),
			static_cast<std::uint8_t>(part0),
			static_cast<std::uint8_t>(part1 >> 8),
			static_cast<std::uint8_t>(part1),
			static_cast<std::uint8_t>(part2 >> 8),
			static_cast<std::uint8_t>(part2),
			static_cast<std::uint8_t>(part3 >> 8),
			static_cast<std::uint8_t>(part3),
			static_cast<std::uint8_t>(part4 >> 8),
			static_cast<std::uint8_t>(part4),
			static_cast<std::uint8_t>(part5 >> 8),
			static_cast<std::uint8_t>(part5),
			static_cast<std::uint8_t>(part6 >> 8),
			static_cast<std::uint8_t>(part6),
			static_cast<std::uint8_t>(part7 >> 8),
			static_cast<std::uint8_t>(part7) }
	{}

	constexpr ipv6_address::ipv6_address(
		const std::uint16_t(&parts)[8])
		: ipv6_address(
			parts[0], parts[1], parts[2], parts[3],
			parts[4], parts[5], parts[6], parts[7])
	{}

	constexpr ipv6_address::ipv6_address(const std::uint8_t(&bytes)[16])
		: bytes_{
			bytes[0], bytes[1], bytes[2], bytes[3],
			bytes[4], bytes[5], bytes[6], bytes[7],
			bytes[8], bytes[9], bytes[10], bytes[11],
			bytes[12], bytes[13], bytes[14], bytes[15] }
	{}

	constexpr std::uint64_t ipv6_address::subnet_prefix() const
	{
		return
			static_cast<std::uint64_t>(bytes_[0]) << 56 |
			static_cast<std::uint64_t>(bytes_[1]) << 48 |
			static_cast<std::uint64_t>(bytes_[2]) << 40 |
			static_cast<std::uint64_t>(bytes_[3]) << 32 |
			static_cast<std::uint64_t>(bytes_[4]) << 24 |
			static_cast<std::uint64_t>(bytes_[5]) << 16 |
			static_cast<std::uint64_t>(bytes_[6]) << 8 |
			static_cast<std::uint64_t>(bytes_[7]);
	}

	constexpr std::uint64_t ipv6_address::interface_identifier() const
	{
		return
			static_cast<std::uint64_t>(bytes_[8]) << 56 |
			static_cast<std::uint64_t>(bytes_[9]) << 48 |
			static_cast<std::uint64_t>(bytes_[10]) << 40 |
			static_cast<std::uint64_t>(bytes_[11]) << 32 |
			static_cast<std::uint64_t>(bytes_[12]) << 24 |
			static_cast<std::uint64_t>(bytes_[13]) << 16 |
			static_cast<std::uint64_t>(bytes_[14]) << 8 |
			static_cast<std::uint64_t>(bytes_[15]);
	}

	constexpr ipv6_address ipv6_address::unspecified()
	{
		return ipv6_address{};
	}

	constexpr ipv6_address ipv6_address::loopback()
	{
		return ipv6_address{ 0, 0, 0, 0, 0, 0, 0, 1 };
	}

	constexpr bool ipv6_address::operator==(const ipv6_address& other) const
	{
		for (int i = 0; i < 16; ++i)
		{
			if (bytes_[i] != other.bytes_[i]) return false;
		}
		return true;
	}

	constexpr bool ipv6_address::operator!=(const ipv6_address& other) const
	{
		return !(*this == other);
	}

	constexpr bool ipv6_address::operator<(const ipv6_address& other) const
	{
		for (int i = 0; i < 16; ++i)
		{
			if (bytes_[i] != other.bytes_[i])
				return bytes_[i] < other.bytes_[i];
		}

		return false;
	}

	constexpr bool ipv6_address::operator>(const ipv6_address& other) const
	{
		return (other < *this);
	}

	constexpr bool ipv6_address::operator<=(const ipv6_address& other) const
	{
		return !(other < *this);
	}

	constexpr bool ipv6_address::operator>=(const ipv6_address& other) const
	{
		return !(*this < other);
	}
}