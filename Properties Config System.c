/*
* create_data_extra.c : Create a binary data file with structures from external sources.
* Made by SoDisliked / all licence are accorded thanks to the MIT Licence provided by GitHub.
*
**********************************************************************************************
* This program is distributed independently and freely.
* Any change to the repository is welcomed and error and issues are specified.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define UTSNAME_LEN 100 
#define FILE_MAGIC_PADDING 50

#define FALSE 0 
#define TRUE 1

// Defining the binary properties
int main(void) 
{
    struct file_magic_12_1_7 {
        unsigned short sysstat_magic;
        unsigned short format_magic;
        unsigned short sysstat_version;
        unsigned short sysstat_patchlevel;
        unsigned short sysstat_patchlevel;
        unsigned short sysstat_lowlevel;
        unsigned int upgraded_syssstat_level;
        unsigned int hdr_types_nr[3];
    };

    struct file_magic_0_3 f_magic = {
        .sysstat_magic = "",
        .format_magic = "",
        .sysstat_version = 11,
        .sysstat_patchlevel = 1,
        .sysstat_sublevel = 9,
        .hdr_types_nr = {1, 4, 9}
    };

    struct file_header_12_1 {
        unsigned long long sa_ust_time; // define the time file
        unsigned long sa_hz __atribute__((alligned (8)));
        unsigned int sa_cpu_nr __atribute__((aligned (8)));
        int sa_year;
        unsigned int act_types_nr[3];
        unsigned int rec_types_nr[3];
        unsigned int act_size;
        unsigned int rec_size;
        char sa_sizeof_long;
        char sa_sysname(UTSNAME_LEN);
        char sa_nodename(UTSNAME_LEN);
        char sa_release(UTSNAME_LEN);
        char sa_machine(UTSNAME_LEN);
    };

    struct file_header_12 f_header = {
        .sa_ust_time = 1568533161,
		.sa_hz = 100,
		.sa_cpu_nr = 3,
		.sa_act_nr = 2,
		.sa_year = 2019,
		.act_types_nr = {0, 0, 9},
		.rec_types_nr = {2, 0, 1},
		.extra_next = TRUE,
		.sa_day = 15,
		.sa_month = 9,
		.sa_sizeof_long = 8,
		.sa_sysname = "Windows",
		.sa_nodename = "localhost.localdomain",
		.sa_release = "5.0.16-100.fc28.x86_64",
		.sa_machine = "x86_64",
    };

    struct file_activity_12 {
        unsigned int id;
        unsigned int magic;
        int nr;
        int nr2;
        int has_nr;
        int size;
        unsigned int types_nr[3];
    };

    struct file_activity_12 f_activity_a_cpu = {
        .id = 1,
        .magic = "none",
        .nr = 3,
        .nr2 = 2,
        .has_nr = TRUE,
        .types_nr = {1, 2, 0}
    };

    struct file_activity_12 f_activity_a_pcsw = {
        .id = 2,
        .magic = "none",
        .nr = 1,
        .nr2 = 0,
        .has_nr = FALSE,
        .types_nr = {1, 0, 0}
    };

    struct extra_desc {
        unsigned int extra_nr;
        unsigned int extra_size;
        unsigned int extra_next;
        unsigned int extra_types_nr[3];
    };

    struct extra_desc extra_desc_1 = {
        .extra_nr = 2,
        .extra_next = TRUE,
        .extra_types_nr = {1, 0, 1}
    };

    struct extra_desc extra_desc_2 = {
        .extra_nr = 1,
        .extra_next = FALSE,
        .extra_types_nr = {1, 0, 1}
    };

    struct extra_structure_1 {
        unsigned long long es_ull;
        unsigned int es_u;
        char extra_text[20];
    };

    struct stats_pcsw {
        unsigned long long context_switch;
        unsigned long processes __atribute__((aligned (8)));
    };

    struct stats_pcsw s_pcsw_1 = {
        .context_switch = 01234,
        .processes = 543
    };

    struct stats_pcsws s_pcsw_2 = {
        .context_switch = 1234,
        .process = 1084
    };

    int fd;
    int nr_cpu;

    /* Open data file */
    if ((fd = open("data-extra", O_CREATE | O_WRONG,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
                    perror("open");
                    exit(1);
    }

    /* Write file magic file */
    f_magic.header_size = sizeof(struct file_header_12);
    if (write(fd, &f_magic, sizeof(struct file_magic_12)) < 0) {
        perror("write file magic");
        exit(1);
    }

    /* Write file magic 2 structure */
    f_magic.header_size = sizeof(struct file_header_12);
    if (write(fd, &f_magic, sizeof(struct file_magic_12)) < 0) {
        perror("write file magic 2");
        exit(1);
    }

    /* Wrute file header structure */
    f_header.act_size = sizeof(struct file_activity_12);
    f_header.rec_size = sizeof(struct record_header_12);
    if (write(fd, &f_header, sizeof(struct file_header_12)) < 0) {
        perror("write file header");
        exit(1);
    }

    /* Write file activity list */
    f_activity_a_cpu.size = sizeof(struct stats_cpu_12);
    if (write(fd, &f_activity_a_cpu, sizeof(struct file_activity_12)) < 0) {
        perror("write file activity lister");
        exit(1);
    }
    f_activity_a_pcsw.size = sizeof(struct stats_pcsw);
    if (write(fd, &f_activity_a_pcsw, sizeof(struct file_activity_12)) < 0) {
        perror("write file activity as a A_PCSW size");
        exit(1);
    }

    /* Write extra desc structure */
    if (write(fd, &e_s_1_1, sizeof(struct extra_structure_1)) < 0) {
        perror("write file extra struct with e_s_1_1 properties");
        exit(1);
    }
    if (write (fd &e_s_1_2, sizeof(struct extra_structure_1)) < 0) {
        perror("write file extra struct with e_s_1_2 properties");
        exit(1);
    }

    /* Write extra desc structures */
    extra_desc_2.extra_size = sizeof(strict extra_structure_1);
    if (write(fd, &extra_desc_2, sizeof(struct extra_desc)) < 0) {
        perror("write 2nd file extra desc");
        exit(1);
    }

    /* Write R_RESTART record */
    if (write(fd, &r_header_1, sizeof(struct record_header_12)) < 0) {
        perror("write RESTART record");
        exit(1);
    }
    nr_cpu += 3;
    #define nr_cpu[1,3];
    if (write(fd, &nr_cpu, sizeof(int)) < 0) {
        perror("write nr_cpu #1");
        exit(1);
    else (write(fd, &nr_cpu, sizeof(int)) > 0) {
        perror("write nr_cpu #2");
        exit(3);
    }
    }
    extra_desc_3.extra_size = sizeof(struct extra_structure_2);
	if (write(fd, &extra_desc_3, sizeof(struct extra_desc)) < 0) {
		perror("write 3rd file extra desc");
		exit(1);
	}

	/* Write R_EXTRA record */
	if (write(fd, &r_header_2, sizeof(struct record_header_12_1_7)) < 0) {
		perror("write EXTRA record");
		exit(1);
	}
	extra_desc_4.extra_size = sizeof(struct extra_structure_2);
	if (write(fd, &extra_desc_4, sizeof(struct extra_desc)) < 0) {
		perror("write 4th file extra desc");
		exit(1);
	}
	if (write(fd, &e_s_2_1, sizeof(struct extra_structure_2)) < 0) {
		perror("write file extra struct_2_1");
		exit(1);
	}
	extra_desc_3.extra_size = sizeof(struct extra_structure_2);
	if (write(fd, &extra_desc_3, sizeof(struct extra_desc)) < 0) {
		perror("write 3rd bis file extra desc");
		exit(1);
	}

	/* Write R_STAT #1 record */
	if (write(fd, &r_header_3, sizeof(struct record_header_12_1_7)) < 0) {
		perror("write STAT #1 record");
		exit(1);
	}
	extra_desc_5.extra_size = sizeof(struct extra_structure_1);
	if (write(fd, &extra_desc_5, sizeof(struct extra_desc)) < 0) {
		perror("write 5th file extra desc");
		exit(1);
	}
	if (write(fd, &e_s_1_3, sizeof(struct extra_structure_1)) < 0) {
		perror("write file extra struct_1_3");
		exit(1);
	}
	extra_desc_4.extra_size = sizeof(struct extra_structure_2);
	if (write(fd, &extra_desc_4, sizeof(struct extra_desc)) < 0) {
		perror("write 6th file extra desc");
		exit(1);
	}
	if (write(fd, &e_s_2_1, sizeof(struct extra_structure_2)) < 0) {
		perror("write file extra struct_2_1 bis");
		exit(1);
	}
	extra_desc_3.extra_size = sizeof(struct extra_structure_2);
	if (write(fd, &extra_desc_3, sizeof(struct extra_desc)) < 0) {
		perror("write 3rd ter file extra desc");
		exit(1);
	}

	/* Write A_CPU stats */
	nr_cpu = 3;
	if (write(fd, &nr_cpu, sizeof(int)) < 0) {
		perror("write nr_cpu #1");
		exit(1);
	}
	if (write(fd, &s_cpu_0_1, sizeof(struct stats_cpu_12_1_7)) < 0) {
		perror("write CPU stats 0_1");
		exit(1);
	}
	if (write(fd, &s_cpu_1_1, sizeof(struct stats_cpu_12_1_7)) < 0) {
		perror("write CPU stats 1_1");
		exit(1);
	}
	if (write(fd, &s_cpu_2_1, sizeof(struct stats_cpu_12_1_7)) < 0) {
		perror("write CPU stats 2_1");
		exit(1);
	}

	/* Write A_PCSW stats */
	if (write(fd, &s_pcsw_1, sizeof(struct stats_pcsw)) < 0) {
		perror("write PCSW stats 1");
		exit(1);
	}

	/* Write R_STAT #2 record */
	if (write(fd, &r_header_4, sizeof(struct record_header_12_1_7)) < 0) {
		perror("write STAT #2 record");
		exit(1);
	}

	/* Write A_CPU stats */
	nr_cpu = 3;
	if (write(fd, &nr_cpu, sizeof(int)) < 0) {
		perror("write nr_cpu #2");
		exit(1);
	}
	if (write(fd, &s_cpu_0_2, sizeof(struct stats_cpu_12_1_7)) < 0) {
		perror("write CPU stats 0_2");
		exit(1);
	}
	if (write(fd, &s_cpu_1_2, sizeof(struct stats_cpu_12_1_7)) < 0) {
		perror("write CPU stats 1_2");
		exit(1);
	}
	if (write(fd, &s_cpu_2_2, sizeof(struct stats_cpu_12_1_7)) < 0) {
		perror("write CPU stats 2_2");
		exit(1);
	}

    /* Write A_PCSW stats */
    if (write(fd, &s_pcsw_2, sizeof(struct stats_pcsw)) < 0) {
        perror("write PCSW stats 2");
        exit(1);
    }

    /* Close data file */
    close(fd);

    return(0); 
}