#ifndef QCSIM_H
#define QCSIM_H

#include "pci.h"

#define QC_BASE 0xFEA00000
#define QC_DMA 0xFEA40000
 
#define QC_DMA_SRC 0x80
#define QC_DMA_DST 0x88
#define QC_DMA_CNT 0x90
#define QC_DMA_CMD 0x98

#define QC_CMD_READ 0x7
#define QC_CMD_WRITE 0x5

void qc_dma_read(uint8_t* buffer, size_t len) {
	mmio_write32(QC_DMA, QC_BASE, QC_DMA_SRC);
	mmio_write32((uint32_t)buffer, QC_BASE, QC_DMA_DST);
	mmio_write32(len, QC_BASE, QC_DMA_CNT);
	mmio_write32(QC_CMD_READ, QC_BASE, QC_DMA_CMD);

	
}


void qc_dma_write(uint8_t* buffer, size_t len) {
	mmio_write32((uint32_t)buffer, QC_BASE, QC_DMA_SRC);
	mmio_write32(QC_DMA, QC_BASE, QC_DMA_DST);
	mmio_write32(len, QC_BASE, QC_DMA_CNT);
	mmio_write32(QC_CMD_WRITE, QC_BASE, QC_DMA_CMD);

}



#endif
