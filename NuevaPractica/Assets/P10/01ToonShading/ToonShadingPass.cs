using System.Numerics;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.RenderGraphModule;
using UnityEngine.Rendering.RenderGraphModule.Util;
using UnityEngine.Rendering.Universal;

public class ToonShadingPass : ScriptableRenderPass
{
    Material _mat;

    public void Setup(int factor, Material material)
    {
        _mat = material;
        int id = Shader.PropertyToID("_factor");
        _mat.SetFloat(id, factor);
    }

    public override void RecordRenderGraph(RenderGraph renderGraph, ContextContainer frameData)
    {
        // UniversalResourceData es un cajon desastre de recursos
        UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();

        // cogemos la textura actual
        var source = resourceData.activeColorTexture;

        var destinationDesc = renderGraph.GetTextureDesc(source);
        destinationDesc.name = "ToonShading";
        TextureHandle destination = renderGraph.CreateTexture(destinationDesc);

        // crea nodo
        RenderGraphUtils.BlitMaterialParameters blitParams =
            new RenderGraphUtils.BlitMaterialParameters(source, destination, _mat, 0);

        renderGraph.AddBlitPass(blitParams, "ToonShadingPass");
        resourceData.cameraColor = destination;
    }
}
