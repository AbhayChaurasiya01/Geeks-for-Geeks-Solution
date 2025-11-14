# Function to join given bound_by and tag
def join_middle(bound_by, tag_name):
    # Get middle index of the bound_by string
    mid = len(bound_by) // 2

    # Insert tag_name exactly in the middle using slicing
    return bound_by[:mid] + tag_name + bound_by[mid:]
