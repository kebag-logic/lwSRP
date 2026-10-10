/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Transmit-opportunity trace for tests/check_equivalence.py.
 *
 * Preloaded into an unmodified unit-test executable, it wraps mrp_transmit
 * and the host send callback. Each offered MRPDU is decoded with the
 * test-side decoder (IEEE 802.1Q-2018 10.8.1.2, 10.8.2). One record per send
 * and one per call are appended to the file named by LWSRP_TRANSMIT_TRACE.
 */
#define _GNU_SOURCE
#include <dlfcn.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <cgreen/breadcrumb.h>
#include <cgreen/reporter.h>

#include "shish_lan/mrp.h"
#include "mrpdu_decoder.h"

typedef int (*transmit_fn)(struct mrp_app *app, uint8_t port_id, uint8_t *pdu,
                           size_t capacity, mrp_send_fn send, void *ctx);

struct relay {
    mrp_send_fn send;
    void *ctx;
    const struct mrp_app *app;
    unsigned sends;
};

static char record[1u << 16];
static size_t used;
static char test[256];
static unsigned opportunity;

static void put(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int n = vsnprintf(record + used, sizeof(record) - used, format, args);
    va_end(args);
    if (n > 0) {
        used += (size_t)n < sizeof(record) - used ? (size_t)n : sizeof(record) - used - 1u;
    }
}

static void flush_record(void)
{
    const char *path = getenv("LWSRP_TRANSMIT_TRACE");
    put("\n");
    if (path) {
        int fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd >= 0) {
            ssize_t written = write(fd, record, used);
            (void)written;
            close(fd);
        }
    }
    used = 0;
}

/* The running cgreen test, which keys every record. */
static const char *current_test(void)
{
    TestReporter *reporter = get_test_reporter();
    const char *name = reporter && reporter->breadcrumb ?
        get_current_from_breadcrumb(reporter->breadcrumb) : NULL;
    return name ? name : "-";
}

static void describe(const struct mrp_app *app, const uint8_t *pdu, size_t len)
{
    static struct mrpdu_decoded d;
    struct mrpdu_profile profile = mrpdu_profile_for(app->ops->ethertype);
    for (size_t k = 0; k < len; ++k) {
        put("%02x", pdu[k]);
    }
    if (mrpdu_decode(pdu, len, &profile, &d) < 0) {
        put("\tundecodable\t");
        return;
    }
    put("\t");
    for (size_t m = 0; m < d.messages; ++m) {
        put("%s%ux%zu", m ? "," : "", d.message[m].type, d.message[m].vectors);
    }
    put(";E%u;T%zu\t", d.end_marks, d.trailing);
    for (size_t k = 0; k < d.vectors; ++k) {
        const struct mrpdu_vector *v = &d.vector[k];
        if (v->leave_all) {
            put(" LA%u", v->type);
        }
        for (unsigned n = 0; n < v->values; ++n) {
            put(" %u:", v->type);
            for (unsigned b = 0; b < v->length; ++b) {
                put("%02x", v->first_value[b]);
            }
            put("+%u:%u", n, mrpdu_event(v, n));
            if (v->four) {
                put(":%u", mrpdu_four_packed(v, n));
            }
        }
    }
}

static int relay_send(void *ctx, uint8_t port, const uint8_t *pdu, size_t len)
{
    struct relay *r = ctx;
    int rc = r->send(r->ctx, port, pdu, len);
    put("S\t%s\t%u\t%u\t%04x\t%u\t%d\t%zu\t", test, opportunity, r->sends,
        r->app->ops->ethertype, port, rc, len);
    describe(r->app, pdu, len);
    flush_record();
    ++r->sends;
    return rc;
}

int mrp_transmit(struct mrp_app *app, uint8_t port_id, uint8_t *pdu, size_t capacity,
                 mrp_send_fn send, void *ctx)
{
    static transmit_fn real;
    if (!real) {
        real = (transmit_fn)dlsym(RTLD_NEXT, "mrp_transmit");
    }
    const char *name = current_test();
    if (strcmp(name, test) != 0) {
        snprintf(test, sizeof(test), "%s", name);
        opportunity = 0;
    }
    struct relay r = {send, ctx, app, 0};
    int result = real(app, port_id, pdu, capacity, send ? relay_send : NULL, &r);
    put("C\t%s\t%u\t%04x\t%u\t%zu\t%d\t%u", test, opportunity,
        app ? app->ops->ethertype : 0u, port_id, capacity, result, r.sends);
    flush_record();
    ++opportunity;
    return result;
}
