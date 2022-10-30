idf_component_register(
	SRCS 	"src/utils.c"
			"profile/profile_util.c"
	INCLUDE_DIRS "inc" "profile"
	REQUIRES perfmon)
