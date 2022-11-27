#ifndef DICPATCHEREPOLL_H
#define DICPATCHEREPOLL_H

#include "Coroutine03/Core/Timeout.h"
#include "EPoll.h"
#include <Poco/SharedPtr.h>
#include <map>
#include <Poco/Optional.h>

namespace Coroutine03 {
	namespace Core {

		class DispatcherEPoll {
		public:
			class Handler {
			public:
				virtual void run(EPoll::Events events) = 0;
				virtual ~Handler(){}
			};

			void subscribe(int fd, EPoll::Events interestedEvents, Poco::SharedPtr<Handler> handler);
			void unsubscribe(int fd);
			void run();

			/** \brief Wait while some events on file descriptor.
			 * 
			 * Execute handlers for events on other file descriptors while
			 * wait events on interested file descriptor.
			 * Exit when events happened on interested file descriptor.
			 * 
			 * \param currentFd an interested file descriptor for wait events.
			 * \param eventMask is filter for events on interested fd. Exit only for events are matched by this mask.
			 * \param timeout is time for wait events. If time is spended exit with 0 value.
			 * \return Flags of happened events or 0 on timeout.
			 * @{
			 */
			EPoll::Events wait(int currentFd, EPoll::Events eventsMask, Timeout timeout);
			EPoll::Events wait(int currentFd, EPoll::Events eventsMask);
			/** @} */
		private:
			EPoll _epoll;
			std::map<int, Poco::SharedPtr<Handler> > _handlers;
		};

	} // namespace Core
} // namespace Coroutine03
#endif // DICPATCHEREPOLL_H