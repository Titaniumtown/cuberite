
#include "Globals.h"
#include "../TestHelpers.h"
#include "ChunkData.h"




/** Performs the entire cChunkData coordinates test. */
static void test()
{
	{
		ChunkBlockData buffer;

		// Empty chunks
		buffer.SetBlock({ 0, 0, 0 }, 0xAB);
		TEST_EQUAL(buffer.GetBlock({ 0, 0, 0 }), 0xAB);
		buffer.SetMeta({ 0, 16, 0 }, 0xC);
		TEST_EQUAL(buffer.GetMeta({ 0, 16, 0 }), 0xC);

		// loaded but not written segments
		TEST_EQUAL(buffer.GetBlock({ 1, 0, 0 }), 0x0);
		TEST_EQUAL(buffer.GetMeta({ 1, 16, 0 }), 0x0);

		// Notloaded segments
		TEST_EQUAL(buffer.GetBlock({ 0, 32, 0 }), 0x0);
		TEST_EQUAL(buffer.GetMeta({ 0, 48, 0 }), 0x0);

		// Out of range GetBlock
		TEST_ASSERTS(
			buffer.GetBlock(-1, 0, 0);
		);
		TEST_ASSERTS(
			buffer.GetBlock(0, -1, 0);
		);
		TEST_ASSERTS(
			buffer.GetBlock(0, 0, -1);
		);
		TEST_ASSERTS(
			buffer.GetBlock(256, 0, 0);
		);
		TEST_ASSERTS(
			buffer.GetBlock(0, 256, 0);
		);
		TEST_ASSERTS(
			buffer.GetBlock(0, 0, 256);
		);

		// Out of range SetBlock
		TEST_ASSERTS(
			buffer.SetBlock({ -1, 0, 0 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetBlock({ 0, -1, 0 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetBlock({ 0, 0, -1 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetBlock({ 256, 0, 0 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetBlock({ 0, 256, 0 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetBlock({ 0, 0, 256 }, 0)
		);

		// Out of range GetMeta
		TEST_ASSERTS(
			buffer.GetMeta(-1, 0, 0);
		);
		TEST_ASSERTS(
			buffer.GetMeta(0, -1, 0);
		);
		TEST_ASSERTS(
			buffer.GetMeta(0, 0, -1);
		);
		TEST_ASSERTS(
			buffer.GetMeta(256, 0, 0);
		);
		TEST_ASSERTS(
			buffer.GetMeta(0, 256, 0);
		);
		TEST_ASSERTS(
			buffer.GetMeta(0, 0, 256);
		);

		// Out of range SetMeta
		TEST_ASSERTS(
			buffer.SetMeta({ -1, 0, 0 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetMeta({ 0, -1, 0 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetMeta({ 0, 0, -1 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetMeta({ 256, 0, 0 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetMeta({ 0, 256, 0 }, 0)
		);
		TEST_ASSERTS(
			buffer.SetMeta({ 0, 0, 256 }, 0)
		);
	}

	{
		ChunkBlockData buffer;

		// Zero's
		buffer.SetBlock({ 0, 0, 0 }, 0x0);
		buffer.SetBlock({ 0, 0, 1 }, 0xab);
		TEST_EQUAL(buffer.GetBlock({ 0, 0, 0 }), 0x0);
		TEST_EQUAL(buffer.GetBlock({ 0, 0, 1 }), 0xab);

		buffer.SetMeta({ 0, 16, 0 }, 0x0);
		buffer.SetMeta({ 0, 16, 1 }, 0xc);
		TEST_EQUAL(buffer.GetMeta({ 0, 16, 0 }), 0x0);
		TEST_EQUAL(buffer.GetMeta({ 0, 16, 1 }), 0xc);
	}


	{
		// Operator =
		ChunkBlockData buffer;
		buffer.SetBlock({ 0, 0, 0 }, 0x42);
		ChunkBlockData copy;
		copy = std::move(buffer);
		TEST_EQUAL(copy.GetBlock({ 0, 0, 0 }), 0x42);
	}
}





IMPLEMENT_TEST_MAIN("ChunkData Coordinates",
	test();
)
