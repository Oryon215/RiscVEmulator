#include <libaio.h>

int main()
{
	unsigned int nr_events = 0;
	aio_context_t* ctx_idp = 1;
	io_setup(nr_events, ctx_idp);

}
