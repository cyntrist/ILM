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

    private class PassData
    {
        public Material material;
    }

    public override void RecordRenderGraph(RenderGraph renderGraph, ContextContainer frameData)
    {
        // UniversalResourceData es un cajon desastre de recursos
        UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();

        // cogemos la textura actual
        var source = resourceData.activeColorTexture;

        // creamos la textura destination textura/target/destino nueva
        // cogemos informacion de la textura source
        var destinationDesc = renderGraph.GetTextureDesc(source);
        destinationDesc.name = "ToonShading";
        TextureHandle destination = renderGraph.CreateTexture(destinationDesc);

        // creamos el nodo
        RenderGraphUtils.BlitMaterialParameters blitParams =
            new RenderGraphUtils.BlitMaterialParameters(source, destination, _mat, 0);

        renderGraph.AddBlitPass(blitParams, "ToonShadingPass");
        resourceData.cameraColor = destination;

        //// anadimos un nodo en el grafo y ese nodo va a recibir en su funcion de renderizado un pass data
        //using (var builder = renderGraph.AddRasterRenderPass<PassData>("ToonShading", out var passData)) // devuelve un constructor de nodo, con esto se abre y luego hay que cerrarlo
        //{
        //    UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();
        //    var source = resourceData.activeColorTexture;
        //    var destinationDesc = renderGraph.GetTextureDesc(source);
        //    destinationDesc.name = $"ToonShading-{passName}";
        //    TextureHandle destination = renderGraph.CreateTexture(destinationDesc);


        //    builder.SetRenderAttachment(destination, 0, AccessFlags.Write);
        //    builder.SetRenderFunc<PassData>(ExecutePass);

        //    passData.factor = _factor; // lo que nosotros pongamos aqui terminara en el ExecutePass

        //    builder.AllowPassCulling(false);
        //}
    }
}
