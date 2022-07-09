#include <net/ip_endpoint.h>

namespace foo::net
{
	std::string ip_endpoint::to_string() const
	{
		return is_ipv4() ? m_ipv4.to_string() : m_ipv6.to_string();
	}

	std::optional<ip_endpoint> ip_endpoint::from_string(std::string_view string) noexcept
	{
		if (auto ipv4 = ipv4_endpoint::from_string(string); ipv4)
		{
			return *ipv4;
		}

		if (auto ipv6 = ipv6_endpoint::from_string(string); ipv6)
		{
			return *ipv6;
		}

		return std::nullopt;
	}
}