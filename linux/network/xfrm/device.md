
xfrm_add_sa -> xfrm_state_construct

xfrm_state_construct -> xfrm_dev_state_add

xfrm_dev_state_add -> dev->xfrmdev_ops->xdo_dev_state_add